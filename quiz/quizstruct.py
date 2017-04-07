class Athlete(object):
    type = 'Athlete'
    all_athletes = []
    
    def __init__(self, name, nationality= 'Blank'):
        self.name = name
        self.nationality = nationality 
        self.all_athletes.append(name)
        
    def compose_print(self):
        return self.type + ', ' + self.name
        
    def __str__(self):
        return self.compose_print()
        
class Swimmer(Athlete):
    type = 'Swimmer'
    
    def __init__(self, name, nationality, distance): 
        Athlete.__init__(self, name, nationality) 
        self.distance = distance
    
    def compose_print(self):
        return self.type + ', ' + self.name + ', ' + \
                str(self.distance)
                
class Runner(Athlete):
    type = 'Runner'
    
    def __init__(self, name, nationality, distance): 
        Athlete.__init__(self, name, nationality) 
        self.distance = distance

class Sprinter(Runner):
    def __init__(self, name, nationality, distance):
        self.name = name
        self.nationality = nationality
        self.distance = distance
        
class Football_player(Athlete):
    type = 'Football_player'
    
    def __init__(self, name, nationality, club):
        Athlete.__init__(self, name, nationality)
        self.club = club
        self.all_athletes = []

    def change_club(self, new_club):
        self.club = new_club

    
# a = Swimmer('Ranomi Kromowidjojo', 'Dutch', '100m')
# b = Sprinter('Usain Bolt', 'Jamaican', '100m')


Swimmer('Ranomi Kromowidjojo', 'Dutch', '100m') 
Football_player('Wayne Rooney', 'English', 'Man Utd') 
Sprinter('Usain Bolt', 'Jamaican', '100m')

print("test")
print (Runner('Khalid Choukoud', 'Dutch', '42.195km').all_athletes)

# print(Swimmer.compose_print(a))
# print(Sprinter.compose_print(b))