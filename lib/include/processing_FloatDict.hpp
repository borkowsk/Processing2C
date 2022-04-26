/// A simple class to use a String as a lookup for an floating point value. 
/// String "keys" are associated with float values.
//*/////////////////////////////////////////////////////////////////////////

class FloatDict
{
public:
        ///Constructor(s)	
        FloatDict();
        //FloatDict(pairs);
        //FloatDict(row);
        
        int     size(); //!<	Returns the number of key/value pairs
        void    clear(); //!<	Remove all entries
        
        ///...
        //iterable<float>        values(); //!< Return the internal array being used to store the values
        
        String[]        keyArray(); //!< Return a copy of the internal keys array
        
        ///...
        float[]         valueArray(); //!< Create a new array and copy each of the values into it
        
        ///...
        float get(String&); //!< Return a value for the specified key
        float get(String& key,float alternate);
        
        ///...
        void set(String& key,float value); //!< Create a new key/value pair or change the value of one
        
        bool hasKey(String& key); //!< Check if a key is a part of the data structure
        int  remove(String& key); //!< Remove a key/value pair
        
        /// Sorting tools:
        void sortKeys(); //!< Sort the keys alphabetically
        void sortKeysReverse(); //!< Sort the keys alphabetically in reverse
        void sortValues(); //!< Sort by values in ascending order
        void sortValuesReverse(); //!< Sort by values in descending order
        
        /// Arthmetics:
        void add(String& key,float val); //!< Add to a value
        void sub(String& key,float val); //!< Subtract from a value
        void div(String& key,float val); //!< Divide a value
        void mult(String& key,float val);//!< Multiply a value
};


//*//////////////////////////////////////////////////////////////////////////////////
// @see: file:///.../processing-3.5.4/modes/java/reference/FloatDict.html
//*//////////////////////////////////////////////////////////////////////////////////
