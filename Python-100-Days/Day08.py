class Student(object):

    def __init__(self, name, age):
        self.name = name
        self.age = age

    def study(self, courseName):
        print("%s is studying %s" % (self.name, courseName))

    def watch_movie(self):
        if self.age < 18:
            print(" Watch some cartoon")
        else:
            print("Watch some adult movie")

    def __privateStudy(self, otherCourse):
        print("%s is studying %s" % (self.name, otherCourse))


def main():
    stud1 = Student("Jaho", 23)
    stud1.watch_movie()
    stud1.study("Computer Graphic")
    stud1._Student__privateStudy("Network")  # Throw error, no attribute
    stud1.gender = "Male"


if __name__ == "__main__":
    main()
