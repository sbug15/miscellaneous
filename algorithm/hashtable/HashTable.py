class Node:

    def __init__(self, data):
        self.data = data
        self.next = None

    @classmethod
    def add(cls, head, data):
        if head == None:
            return Node(data)

        temp = head
        while (temp.next != None):
            temp = temp.next
        temp.next = Node(data)

    @classmethod
    def find(cls, head, data):
        if (head.data == data):
            return head

        temp = head
        while (temp.next != None):
            temp = temp.next
            if (temp.data == data):
                return temp
        return None

    @classmethod
    def printElem(cls, head):
        if head is not None:
            print head.data

        temp = head
        while (temp.next != None):
            temp = temp.next
            print temp.data

    @classmethod
    def remove(cls, head, data):
        if head.data == data:
            return head.next

        temp =head
        while (temp.next != None):
            if (temp.next.data == data):
                temp.next = temp.next.next
            temp = temp.next

    @classmethod
    def countElem(cls, head):
        count = 1

        temp = head
        while (temp.next != None):
            count += 1
            temp = temp.next

        return count

class HashTable:

    def __init__(self, length):
        self.length = length
        self.hashtable = [None] * length

    def hash(self, _str):
        value = 0
        for letter in _str:
            value += ord(letter)

        return value * len(_str) % self.length

    def addElem(self, _str):
        index = self.hash(_str)
        if self.hashtable[index] == None:
            self.hashtable[index] = Node(_str)

        else:
            Node.add(self.hashtable[index], _str)

    def delElem(self, _str):
        index = self.hash(_str)
        if self.hashtable[index] == None:
            return False
        else:
            Node.remove(self.hashtable[index], _str)

    def findElem(self, _str):
        index = self.hash(_str)
        if self.hashtable[index] == None:
            return False
        else:
            Node.find(self.hashtable[index], _str)

    def printElem(self):
        for i in range(self.length):
            if self.hashtable[i] is not None:
                Node.printElem(self.hashtable[i])

arr = [1, 2, 3, 4, 5, 6, 2, -1, 2, 9, 8]
head = Node(10)
for num in arr:
    Node.add(head, num)

Node.printElem(head)
Node.remove(head, 2)
Node.printElem(head)
Node.remove(head, 15)
Node.printElem(head)

table = HashTable(13)
table.addElem('crazy')
table.addElem('I am not')
node = table.findElem('crazy')
table.printElem()
