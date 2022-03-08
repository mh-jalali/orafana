from math import degrees


class celsius:
    def __init__(self , degrees):
        self.degrees = degrees
    
    def farenheit (self):
        return ((self.degrees*9.0)/5.0)+32.0




class Event(object):
 
    def __init__(self):
        self.__eventhandlers = []
 
    def __iadd__(self, handler):
        self.__eventhandlers.append(handler)
        return self
 
    def __isub__(self, handler):
        self.__eventhandlers.remove(handler)
        return self
 
    def __call__(self, *args, **keywargs):
        for eventhandler in self.__eventhandlers:
            eventhandler(*args, **keywargs)