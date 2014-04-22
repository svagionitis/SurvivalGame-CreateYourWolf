#ifndef SLLIST_H
#define SLLIST_H
/*
 * Lock-less NULL terminated single linked list
 *
 * If there are multiple producers and multiple consumers, sllist_add
 * can be used in producers and sllist_del_all can be used in
 * consumers.  They can work simultaneously without lock.  But
 * sllist_del_first can not be used here.  Because sllist_del_first
 * depends on list->first->next does not changed if list->first is not
 * changed during its operation, but sllist_del_first, sllist_add,
 * sllist_add (or sllist_del_all, sllist_add, sllist_add) sequence in
 * another consumer may violate that.
 *
 * If there are multiple producers and one consumer, sllist_add can be
 * used in producers and sllist_del_all or sllist_del_first can be used
 * in the consumer.
 *
 * This can be summarized as follow:
 *
 *           |   add    | del_first |  del_all
 * add       |    -     |     -     |     -
 * del_first |          |     L     |     L
 * del_all   |          |           |     -
 *
 * Where "-" stands for no lock is needed, while "L" stands for lock
 * is needed.
 *
 * The list entries deleted via sllist_del_all can be traversed with
 * traversing function such as sllist_for_each etc.  But the list
 * entries can not be traversed safely before deleted from the list.
 * The order of deleted entries is from the newest to the oldest added
 * one.  If you want to traverse from the oldest to the newest, you
 * must reverse the order by yourself before traversing.
 *
 * The basic atomic operation of this list is cmpxchg on long.  On
 * architectures that don't have NMI-safe cmpxchg implementation, the
 * list can NOT be used in NMI handlers.  So code that uses the list in
 * an NMI handler should depend on CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG.
 *
 * Copyright 2010,2011 Intel Corp.
 *   Author: Huang Ying <ying.huang@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdint.h>
#include <stddef.h>

#ifndef container_of
#define container_of(ptr, type, member) ({                  \
        const typeof(((type *)0)->member) * __mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); })
#endif

#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))


struct sllist_head {
	struct sllist_node *first;
};

struct sllist_node {
	struct sllist_node *next;
};

#define SLLIST_HEAD_INIT(name)	{ NULL }
#define SLLIST_HEAD(name)	struct sllist_head name = SLLIST_HEAD_INIT(name)

static inline uint32_t xchg(uint32_t x, volatile void *ptr)
{
    uint32_t ret;

    ret = *(volatile uint32_t *)ptr;
    *(volatile uint32_t *)ptr = x;

    return ret;
}

static inline uint32_t cmpxchg(volatile void *ptr, uint32_t old, uint32_t new)
{
    uint32_t prev;

    prev = *(uint32_t *)ptr;
    if (prev == old)
        *(uint32_t *)ptr = (uint32_t)new;

    return prev;
}

/**
 * init_sllist_head - initialize lock-less list head
 * @head:	the head for your lock-less list
 */
static inline void init_sllist_head(struct sllist_head *list)
{
	list->first = NULL;
}

/**
 * sllist_entry - get the struct of this entry
 * @ptr:	the &struct sllist_node pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the sllist_node within the struct.
 */
#define sllist_entry(ptr, type, member)		\
	container_of(ptr, type, member)

/**
 * sllist_for_each - iterate over some deleted entries of a lock-less list
 * @pos:	the &struct sllist_node to use as a loop cursor
 * @node:	the first entry of deleted list entries
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being deleted from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself before traversing.
 */
#define sllist_for_each(pos, node)              \
	for ((pos) = (node); pos; (pos) = (pos)->next)

/**
 * sllist_for_each_entry - iterate over some deleted entries of lock-less list of given type
 * @pos:	the type * to use as a loop cursor.
 * @node:	the fist entry of deleted list entries.
 * @member:	the name of the sllist_node with the struct.
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being removed from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself before traversing.
 */
#define sllist_for_each_entry(pos, node, member)                        \
	for ((pos) = sllist_entry((node), typeof(*(pos)), member);      \
	     &(pos)->member != NULL;                                    \
	     (pos) = sllist_entry((pos)->member.next, typeof(*(pos)), member))

/**
 * sllist_for_each_entry_safe - iterate over some deleted entries of lock-less list of given type
 *			       safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @node:	the first entry of deleted list entries.
 * @member:	the name of the sllist_node with the struct.
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being removed from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself before traversing.
 */
#define sllist_for_each_entry_safe(pos, n, node, member)                        \
	for (pos = sllist_entry((node), typeof(*pos), member);                  \
	     &pos->member != NULL &&                                            \
	        (n = sllist_entry(pos->member.next, typeof(*n), member), true); \
	     pos = n)

/**
 * sllist_empty - tests whether a lock-less list is empty
 * @head:	the list to test
 *
 * Not guaranteed to be accurate or up to date.  Just a quick way to
 * test whether the list is empty without deleting something from the
 * list.
 */
static inline bool sllist_empty(const struct sllist_head *head)
{
	return ACCESS_ONCE(head->first) == NULL;
}

static inline struct sllist_node *sllist_next(struct sllist_node *node)
{
	return node->next;
}


/**
 * sllist_add_batch - add several linked entries in batch
 * @new_first:	first entry in batch to be added
 * @new_last:	last entry in batch to be added
 * @head:	the head for your lock-less list
 *
 * Return whether list is empty before adding.
 */
bool sllist_add_batch(struct sllist_node *new_first, struct sllist_node *new_last,
                      struct sllist_head *head)
{
	struct llist_node *first;

	do {
		new_last->next = first = ACCESS_ONCE(head->first);
	} while (cmpxchg(&head->first, first, new_first) != first);

	return !first;
}

/**
 * sllist_add - add a new entry
 * @new:	new entry to be added
 * @head:	the head for your lock-less list
 *
 * Returns true if the list was empty prior to adding this entry.
 */
static inline bool sllist_add(struct sllist_node *new, struct sllist_head *head)
{
	return sllist_add_batch(new, new, head);
}

/**
 * sllist_del_all - delete all entries from lock-less list
 * @head:	the head of lock-less list to delete all entries
 *
 * If list is empty, return NULL, otherwise, delete all entries and
 * return the pointer to the first entry.  The order of entries
 * deleted is from the newest to the oldest added one.
 */
static inline struct sllist_node *sllist_del_all(struct sllist_head *head)
{
	return xchg(&head->first, NULL);
}

/**
 * sllist_del_first - delete the first entry of lock-less list
 * @head:	the head for your lock-less list
 *
 * If list is empty, return NULL, otherwise, return the first entry
 * deleted, this is the newest added one.
 *
 * Only one llist_del_first user can be used simultaneously with
 * multiple llist_add users without lock.  Because otherwise
 * llist_del_first, llist_add, llist_add (or llist_del_all, llist_add,
 * llist_add) sequence in another user may change @head->first->next,
 * but keep @head->first.  If multiple consumers are needed, please
 * use llist_del_all or use lock between consumers.
 */
struct sllist_node *sllist_del_first(struct sllist_head *head)
{
	struct sllist_node *entry, *old_entry, *next;

	entry = head->first;
	for (;;) {
		if (entry == NULL)
			return NULL;
		old_entry = entry;
		next = entry->next;
		entry = cmpxchg(&head->first, old_entry, next);
		if (entry == old_entry)
			break;
	}

	return entry;
}

struct sllist_node *sllist_reverse_order(struct sllist_node *head);
/**
 * llist_reverse_order - reverse order of a llist chain
 * @head:	first item of the list to be reversed
 *
 * Reverse the order of a chain of llist entries and return the
 * new first entry.
 */
struct sllist_node *sllist_reverse_order(struct sllist_node *head)
{
	struct sllist_node *new_head = NULL;

	while (head) {
		struct sllist_node *tmp = head;
		head = head->next;
		tmp->next = new_head;
		new_head = tmp;
	}

	return new_head;
}

#endif /* SLLIST_H */
