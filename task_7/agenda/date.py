class Date(object):
    """The AgendaDate Class in Agenda."""
    def __init__(self, year=0, month=0, day=0, hour=0, minute=0)
        self.year = year
        self.month = month
        self.day = day
        self.hour = hour
        self.minute = minute

    def __repr__(self):
        return "<Date %r>" % Date.date_to_string(self)

    @staticmethod
    def date_to_string(date):
        pass

    @staticmethod
    def string_to_date(string):
        pass

    @staticmethod
    def isValid(date):
        pass

    def __eq__(date):
        pass

    def __ne__(date):
        pass
    
    def __lt__(date):
        pass

    def __gt__(date):
        pass

    def __ge__(date):
        pass

    def __le__(date):
        pass

    
    
