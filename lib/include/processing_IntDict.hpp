/// A simple class to use a String as a lookup for an integer value. 
/// String "keys" are associated with int values.
//*///////////////////////////////////////////////////////////////////

class IntDict
{
public:
        ///Constructor(s)	
        IntDict();
        //IntDict(pairs);
        //IntDict(row);
        
        int     size(); //!<	Returns the number of key/value pairs
        void    clear(); //!<	Remove all entries
        
        ///...
        //iterable<int>        values(); //!< Return the internal array being used to store the values
        
        String[]        keyArray(); //!< Return a copy of the internal keys array
        
        ///...
        int[]         valueArray(); //!< Create a new array and copy each of the values into it
        
        ///...
        int get(String&); //!< Return a value for the specified key
        int get(String& key,int alternate);
        
        ///...
        void set(String& key,int value); //!< Create a new key/value pair or change the value of one
        
        bool hasKey(String& key); //!< Check if a key is a part of the data structure
        int  remove(String& key); //!< Remove a key/value pair
        
        /// Sorting tools:
        void sortKeys(); //!< Sort the keys alphabetically
        void sortKeysReverse(); //!< Sort the keys alphabetically in reverse
        void sortValues(); //!< Sort by values in ascending order
        void sortValuesReverse(); //!< Sort by values in descending order
        
        /// Arthmetics:
        void add(String& key,int val); //!< Add to a value
        void sub(String& key,int val); //!< Subtract from a value
        void div(String& key,int val); //!< Divide a value
        void mult(String& key,int val);//!< Multiply a value
};


//*//////////////////////////////////////////////////////////////////////////////////
// @see: file:///.../processing-3.5.4/modes/java/reference/IntDict.html
//*//////////////////////////////////////////////////////////////////////////////////
