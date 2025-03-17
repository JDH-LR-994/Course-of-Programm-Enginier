package MyCollection.ArrayListAndLinkedList;

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;

import java.util.Iterator;

@EqualsAndHashCode
public class MyLinkedList<T> implements MyList<T> {
    @Override
    public void add(T t) {
        if (size == 0) {
            head = new Node(null, t, null);
            tail = head;
        } else {
            Node secondTail = tail;
            tail = new Node(secondTail, t, null);
            secondTail.next = tail;
        }
        size++;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public T get(int index) {
        return getNode(index).value;
    }

    @Override
    public boolean removeAt(int index) {
        Node node = getNode(index);
        Node nextNode = node.next;
        Node nodePrev = node.previous;
        if (nextNode != null) {
            nextNode.previous = nodePrev;

        } else {
            tail = nodePrev;
        }
        if (nodePrev != null) {
            nodePrev.next = nextNode;
        } else {
            head = nextNode;
        }
        size--;
        return true;
    }

    @Override
    public void clear() {
        head = null;
        tail = null;
        size = 0;
    }

    @Override
    public void insert(T t, int index) throws IndexOutOfBoundsException {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }
        if (index == size) {
            add(t);
            return;
        }
        Node nodeNext = getNode(index);
        Node nodePrev = nodeNext.previous;
        Node newNode = new Node(nodePrev, t, nodeNext);
        nodeNext.previous = newNode;
        if (nodePrev != null) {
            nodePrev.next = newNode;
        } else {
            head = newNode;
        }
        size++;
    }

    @Override
    public boolean remove(T item) {
        Node node = head;
        for (int i = 0; i < size; i++) {
            if (item.equals(node.value)) {
                return removeAt(i);
            }
            node = node.next;
        }
        return false;
    }

    @Override
    public Iterator<T> iterator() {
        return new Iterator<>() {

            private Node node = head;

            @Override
            public boolean hasNext() {
                return node != null;
            }

            @Override
            public T next() {
                T value = node.value;
                node = node.next;
                return value;
            }
        };
    }

    @AllArgsConstructor
    private class Node {
        Node previous;
        T value;
        Node next;
    }

    private Node getNode(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException();
        }
        Node current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current;
    }

    private Node head;
    private Node tail;
    private int size;
}
