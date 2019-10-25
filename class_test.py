class Student(object):
    def __init__(self, name, gender):
        self.name = name
        self.__gender = gender
    def get_gender(self):
        return self.__gender
    def set_gender(self,A):
        if A=='male' or A=='female':
            self.__gender=A
        else:
            raise ValueError('invald')
class Animal(object):
    def run(self):
        print('Animal is running')
class Dog(Animal):
    def run(self):
        print('Dog is running')
    def run_twice(self,animal):
        animal.run()
        animal.run()


if __name__ == '__main__':
    dog=Dog()
    # Animal=An
    dog.run_twice(Dog())