class Human(object):
    def __init__(self, name, length, age):
        self.name = name
        self.age = age
        self.length = length

    def age_times_length(self):
        return self.age * self.length

    def grow(self, new_length):
        self.length = new_length

class Football_player(Human):
    def __init__(self, name, club, length, age):
        Human.__init__(self, name, length, age)
        self.club = club

    def change_club(self, new_club):
        self.club = new_club

    def get_age(self):
        return self.age
    
    def print_self(self):
        print(self.name, self.club, self.length, self.age)

class Student(Human):
    def __init__(self, name_deze, length, grade, age):
        super().__init__(age = age, name = name_deze, length = length)
        self.grade = grade

    def print_self(self):
        print(self.name, self.age, self.length)

    def to_the_power_of(self, x, y):
        return x**y

# def strip_human_of_name(ding):
#     ding.name = ""

human1 = Student("hans", 125, 10, 21)
print(human1.__dict__)
human1.print_self()
human1.grow(444)
human1.print_self()
human2 = Student("kees", 126, 11, 22)
print(human2.__dict__)
human2.print_self()
print(human2.to_the_power_of(5,5))


human3 = Football_player("kees", "club", 11, 44)
human3.print_self()
# hans = Student("hansje", 125, 10, age = 21)
# print(hans)
# hans.print_self()
# print(hans.age_times_length())
# # Vraag hans waarom hij een 10 heeft
# print(hans.to_the_power_of(666, 2))
# hans.grow(210)
# hans.print_self()
# hans.name = 12
# #hans.change_name("hans")
# hans.print_self()
# print(hans.length)