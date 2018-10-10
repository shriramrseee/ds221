
class IDictionary
{
	public:
    
	// Virtual function to insert new key value pair into the dictionary
    virtual void insert (int , char* )=0; 

	// Virtual functin to lookup a value in the dictionary based on the key
    virtual char* lookup (int)=0; 
	
	
};

