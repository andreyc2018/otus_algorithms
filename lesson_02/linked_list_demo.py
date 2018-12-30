"""
Cвязный список можно реализовать так
"""

class ListItem:
    """
    Элемент связного списка (в конце файла - вариант реализации через @property)
    """
    def __init__(self, value=None):
        self.value = value
        self._next = None

    @property
    def next(self):  # Это тоже
        return self._next

    @next.setter
    def next(self, item):  # Это проще реализовать как @property
        self._next = item


    def __repr__(self):
        return str(self.value)


class LinkedList:
    """
    Связный список
    """
    def __init__(self):
        self._head = None
        self._tail = None

    def append(self, item):
        item = ListItem(item)
        if self._head is None:
            self._head = item
            self._tail = item
        else:
            self._tail.next = item
            self._tail = item

    def __iter__(self):
        """
        Вопрос: почему лучше использовать отдельный LinkedListIterator, а не итерировать прямо из класса?
        :return:
        """
        return LinkedListIterator(self)

    def __str__(self):
        return ", ".join([str(item) for item in self])

    def remove(self, element):
        raise NotImplementedError

    def search(self, element):
        raise NotImplementedError



class LinkedListIterator:
    def __init__(self, llist):
        """
        Реализуйте итератор для связного списка
        hint: можно использовать указатель на текущий элемент
        :param llist:
        """
        raise NotImplementedError

    def __next__(self):
        raise NotImplementedError


if __name__ == '__main__':
    llist = LinkedList()

    for i in range(100):
        print(i, end=', ')
        llist.append(i)

    print('\nКонец списка: {}'.format(llist._tail))
    print('Следующий за head элемент: {}'.format(llist._head.next))
    print('Следующий за head.next элемент: {}'.format(llist._head.next.next))
    # ...Отталкиваясь от этого, можно реализовать __next__() для LinkedListIterator'а

    # Обратите внимание: здесь будет срабатывать NotImplementedError, пока нет реализации у LinkedListIterator
    print(llist)
