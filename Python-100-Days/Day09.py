from abc import ABCMeta, abstractmethod


class Student(object):

    # __slots__ = ("_name", "_age")  # this Class can only hold _name and _age

    def __init__(self, name, age):
        self._name = name
        self._age = age

    @property
    def name(self):  # name getter
        return self._name

    @property  # age getter
    def age(self):
        return self._age

    @age.setter  # age setter
    def age(self, age):
        self._age = age

    def study(self, courseName):
        print("%s is studying %s" % (self._name, courseName))

    def watch_movie(self):
        if self._age < 18:
            print(" Watch some cartoon")
        else:
            print("Watch some adult movie")

    def __privateStudy(self, otherCourse):
        print("%s is studying %s" % (self._name, otherCourse))

    @staticmethod
    def Report():
        print("There is a student")

    @classmethod
    def GenerateToolGut(cls):
        return cls("ToolGuy", 18)


class UnderGraduateStudent(Student):

    def __init__(self, name, age, despline):
        super().__init__(name, age)
        self._despline = despline

    def study(self, courseName):  # override the method
        print("%s in %s is studying %s" %
              (self._name, self._despline, courseName))


class Pet(object, metaclass=ABCMeta):

    def __init__(self, nickname):
        self._nickname = nickname

    @abstractmethod
    def make_voice(self):
        pass


class DOG(Pet):

    def make_voice(self):
        print("WOWOWO ", self._nickname)


class CAT(Pet):

    def make_voice(self):
        print("MIAMIAMIA", self._nickname)


def main():
    stud1 = Student("Jaho", 23)
    stud1.age = 10
    # stud1.name="Ben" #Throw error, can't set attribute
    stud1.watch_movie()
    stud1.study("Computer Graphic")
    stud1._Student__privateStudy("Network")  # Throw error, no attribute
    # stud1.gender = "Male" # if line3 __slots__ existed,this will throw no attribute error
    Student.Report()

    toolGuy = Student.GenerateToolGut()
    toolGuy.watch_movie()

    uStud1 = UnderGraduateStudent("Alice", 25, "Computer")
    uStud1.study("DataBase")

    pets = [DOG("DoDO"), CAT("MiMi")] #poly-morphism

    for pet in pets:
        pet.make_voice()


if __name__ == "__main__":
    main()
