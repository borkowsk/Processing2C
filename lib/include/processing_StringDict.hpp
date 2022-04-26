/// A simple class to use a String as a lookup for an String value. 
/// String "keys" are associated with String values.
//*///////////////////////////////////////////////////////////////////

class StringDict
{
public:
        ///Constructor(s)	
        StringDict();
        //StringDict(pairs);
        //StringDict(row);
        
        int     size(); //!<	Returns the number of key/value pairs
        void    clear(); //!<	Remove all entries
        
        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_values_.html
        //iterable<String>        values(); //!< Return the internal array being used to store the values
        
        String[]        keyArray(); //!< Return a copy of the internal keys array
        
        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_valueArray_.html
        String[]        valueArray(); //!< Create a new array and copy each of the values into it
        
        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_get_.html
        String get(String&); //!< Return a value for the specified key
        String get(String& key,String& alternate);
        
        ///file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict_set_.html
        void set(String& key,String& value); //!< Create a new key/value pair or change the value of one
        
        bool hasKey(String& key); //!< Check if a key is a part of the data structure
        String remove(String& key); //!< Remove a key/value pair
        
        /// Sorting tools:
        void sortKeys(); //!< Sort the keys alphabetically
        void sortKeysReverse(); //!< Sort the keys alphabetically in reverse
        void sortValues(); //!< Sort by values in ascending order
        void sortValuesReverse(); //!< Sort by values in descending order
};


//*//////////////////////////////////////////////////////////////////////////////////
// @see: file:///home/borkowsk/processing-3.5.4/modes/java/reference/StringDict.html
//*//////////////////////////////////////////////////////////////////////////////////
