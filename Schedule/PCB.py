# -*- coding: utf-8 -*-
# author: Green Ge
# project: Quantum-based PCB simulation
# software: Atom
# last modified: 4/10/2022 12:31
class ListNode:

    def __init__(self, cur=None, next=None):
        self.cur = cur  # data item
        self.next = next  # pointer to next node
        self.__cur = self  # latest element in the list

    def pop(self):
        '''Returns and removes the earliest element in the list.'''
        if self.next:
            cur = self.next.cur  # skip header element

            if self.next.next:
                self.next = self.next.next
            else:
                # in case of pointer `next` of null of element to be popped out
                self.next = None

            return cur
        else:
            raise IndexError('list is empty')

    def append(self, item):
        '''Appends a `ListNode` object at the end of the list'''
        self.__cur.next = ListNode(item)
        self.__cur = self.__cur.next


class QuantumControl:
    def __init__(self, proc_num):
        self._wait = ListNode()  # blocking queue
        self._ready = ListNode()  # ready queue
        self._executing = None  # process given access to CPU
        self.proc_num = proc_num  # allows a maximum of 3 threads running on CPU
        self._pool = list(range(1, proc_num+1))  # PID pool

    def fork(self, target):
        '''Accepts a new target and put it into a proper list.

        A process will be built for the target and appended at the end of ready
         queue if the queue is not full, otherwise the target itself
         (in this case an integer, i.e. no process will be built) will be
         appended directly at the end of blocking queue.
        '''
        if self._pool:
            p = QuantumProcess(target, self._pool.pop(0))
            self._ready.append(p)
        else:
            self._wait.append(target)  # wait for blocking

    def schedule(self):
        '''Start CPU access allocation.
        '''
        while self._ready.next is not None:
            self._executing = self._ready.pop()
            print(
                'Proecess ', self._executing.get_pid(), ' with remaining time slices: ', self._executing.get_remaining()," is running.",
                sep='',
            )
            self._executing.run()

            if self._executing.status == 0:
                if self._wait.next:
                    self.proc_num += 1
                    self._pool.append(self.proc_num)
                    self.fork(self._wait.pop())  # fetch a suspended process
            else:
                self._ready.append(self._executing)


class QuantumProcess:
    def __init__(self, target, id):
        self.target = target  # user program
        self.id = id
        self.context = 0
        self.status = 1  # 0: finished 1: ready 2: suspended

    def run(self):
        try:
            if self.context < self.target-1:
                # time slice
                for i in range(10000000):
                    pass
                self._suspend()
            else:
                for i in range(10000000):
                    pass
                raise ValueError
        except (ValueError, KeyboardInterrupt):
            self._exit()

    def _suspend(self):
        self.context += 1
        self.status = 2

    def _exit(self):
        self.context += 1
        self.status = 0
        print(
            'Proecess with pid :', self.get_pid(), '  context with :' , self.context," has been finished",
            sep='',
        )

    def get_pid(self):
        return self.id

    def get_remaining(self):
        return self.target - self.context


def main():
    qtm_ctrl = QuantumControl(3)
    qtm_ctrl.fork(7)
    qtm_ctrl.fork(5)
    qtm_ctrl.fork(3)
    qtm_ctrl.fork(2)
    qtm_ctrl.fork(2)
    qtm_ctrl.schedule()


if __name__ == '__main__':
    main()
