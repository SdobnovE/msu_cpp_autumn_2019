import copy
class FragileDict:
    
    def __init__(self, dic=None):
        self._lock = 1
        if dic is not None and type(dic) == dict:
            self._data = copy.deepcopy(dic)
        else:
            self._data = {}
        self._lock = 0
        
        
    def __getitem__(self, arg):
        
        if arg in self._data.keys():
            if self._lock == 0:
                return copy.deepcopy(self._data[arg])
            else:
                return self._data[arg]
                
        else:
            raise KeyError(arg)
        
    
    def __setitem__(self, key, value):
        
        if self._lock == 0:
            raise RuntimeError("Protected state")
        else:
            if key in self._data.keys():
                self._data[key] = value
            else:
                self._data.setdefault(key, value)
                
    
    def __enter__(self):
        self._lock = 1
        self._dataCopy = copy.deepcopy(self._data)
        return self
        
    
    def __exit__(self, exc_type, exc_value, traceback):
        if exc_type is not None:
            print("Exception has been suppressed.")
            self._data = copy.deepcopy(self._dataCopy)
            self._lock = 0
            delattr(self, "_dataCopy")
            return True
        else:
            self._data = copy.deepcopy(self._data)
            self._lock = 0
            delattr(self, "_dataCopy")
           
    def __contains__(self, item):
        return item in self._data
