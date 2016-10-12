class User(object):
    """The AgendaUser Class in Agenda."""
    def __init__(self, name="", password="", email="", phone=""):
        self.name = name
        self.password = password
        self.email = email
        self.phone = phone

    def __repr__(self):
        return "<User %r>" % self.name
