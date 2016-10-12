class Meeting(object):
    """The AgendaMeeting Class in Agenda."""
    def __init__(self, sponsor="", participator="", start_time="",
            end_time="", title=""):
        self.sponsor = sponsor
        self.participator = participator
        self.start_time = start_time
        self.end_time = end_time
        self.title = title

    def __repr__(self):
        return "<Meeting %r>" % self.title

    def is_participator(self, username):
        return username in self.participator
