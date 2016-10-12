class Storage(object):
    """The AgendaStorage Class in Agenda."""
    instance = None

    def __init__(self):
        if instance is None:
            self.user_list = []
            self.meeting_list = []
            is_dirty = False
        else:
            # self = instance
            raise ValueError("Singleton Mode")

    def __repr__(self):
        return "<Storage %r>" % self.name

    def _read_from_file(self):
        pass

    def _write_to_file(self):
        pass

    def create_user(self, user):
        pass

    def query_user(self, filter_):
        pass

    def update_user(self, filter_, switcher):
        pass

    def delete_user(self, filter_):
        pass

    def create_meeting(self, meeting):
        pass

    def query_meeting(self, filter_):
        pass

    def update_meeting(self, filter_, switcher):
        pass

    def delete_meeting(self, filter_):
        pass

    def sync(self):