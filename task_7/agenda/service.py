from storage import storage 
class Service(object):
    """The AgendaService Class in Agenda."""
    def __init__(self, _storage):
        self._storage = _storage
    
    def user_log_in(self, username, password):
        pass

    def user_register(self, username, password, email, phone):
        pass
        
    def delete_user(self, username, password):
        pass
        
    def list_all_users(self):
        pass
        
    def create_meeting(self, username, title, start_date, end_date,
            participator):
        pass
        
    def meeting_query(self, username, title=None,
            start_date=None, end_date=None):
        if title is not None:
            pass
        elif start_date is not None and end_date is not None:
            pass
        else:
            raise ValueError()
        
    def list_all_meetings(self, username):
        pass
        
    def list_all_sponsor_meetings(self, username):
        pass
        
    def list_all_participate_meetings(self, username):
        pass
        
    def delete_meeting(self, username, title):
        pass
        
    def delete_all_meetings(self, username):
        pass
        
    def start_agenda(self):
        pass
        
    def quit_agenda(self):
        pass
        