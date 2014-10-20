#include<iostream>
using namespace std;

char* append(char* str, int length);
char* del(char* str, int length);
void exit(bool &keep_looping);
char* insert(char* str, int length);
char* replace(char* str, int length);
int search(char* str, int &len, char* substr, int &substr_len);

char* get_string(int&);
void get_char(char*);

int main() {

  char* choice = new char[1];
  int length;
  bool keep_looping = true;

  cout << "Enter working string: ";
  char* working_string = get_string(length);
  cout << "You entered: " << working_string << endl;
  
  while (keep_looping) {

    std::cout << "Enter choice: " << std::endl;
    std::cout 
      << "s - search" << std::endl
      << "i - insert" << std::endl
      << "a - append" << std::endl
      << "d - delete" << std::endl
      << "r - replace" << std::endl
      << "e - exit" << std::endl;
    get_char(choice);

    switch(*choice) {

      case 's':

        cout << "search selected" << endl;
        cin.ignore(); // Manual buffer flush needed before reading in new substr.
        
        int substr_len;
        cout << "Enter the substring to search for: ";
        char* substr;
        substr = get_string(substr_len);
        cout << "You entered : " << substr << endl;
        cout << "Searching for " << substr << " in " << working_string << "." << endl;

        int index_found;
        index_found = search(working_string, length, substr, substr_len);
        
        if (index_found == -1)
          cout << "Substring not found." << endl;
        else 
          cout << "Substring found at " << index_found << endl;

        break;

      case 'i': 

        cout << "insert selected" << endl;
        cin.ignore();
        working_string = insert(working_string, length);
        cin.ignore();
        break;

      case 'a':

        cout << "append selected" << endl;
        cin.ignore();
        working_string = append(working_string, length);
        break;

      case 'd': 

        cout << "delete selected" << endl;
        cin.ignore();
        working_string = del(working_string, length);
        break;

     case 'r': 

        cout << "replace selected" << endl;
        cin.ignore();
        working_string = replace(working_string, length);
        break;

      case 'e': 

        cout << "exit selected" << endl;
        exit(keep_looping);
        break;

      default: 

        cout << "invalid selection, please try again" << endl;
    }
    cout << endl;
  }

  return 0;
}

int search(char* str, int &len, char* substr, int &substr_len) {


  // Look at every char in the original string.
  for (int i = 0; i < len; i++) {
    
    // Stop when some char matches the first char of substr.
    if (*(str+i) == *(substr)) {
      
      // See if substr matches up with the next j chars of working string.
      for (int j = 0; j < substr_len; j++) {
        
        // All the chars matched, i was the index where substr occurred.
        if (j == substr_len || *(substr + j) == '\0') return i;

        // Found a mismatched char
        if (*(str+i+j) != *(substr + j)) break;
      }
    }
  }

  // Substring wasn't found.
  return -1;
}

void exit(bool &keep_looping) {
  keep_looping = false;
}

char* get_string(int &len_container) {


    int max_size = 50;
    char* str_container = (char*) malloc(sizeof(char)*max_size);
	fgets(str_container, 50, stdin);

	len_container= strlen(str_container);
	
    str_container = (char*) realloc (
        str_container, sizeof(char) * len_container
    );

    size_t ln = strlen(str_container) - 1;
    if (str_container[ln] == '\n')
          str_container[ln] = '\0';

    return str_container;
}

void get_char(char* c) {
  
  if (!c) c = (char*) malloc(sizeof(char));
  *c = getchar();
}

char* insert(char* str, int length) {

  cout << "Enter substring to insert: ";
  int substr_len;
  char* substr = get_string(substr_len);
  
  cout << "Enter the index into which the substring will be inserted: ";
  int index;
  cin >> index;

  cout << "Inserting '" << substr 
    << "' into '" << str 
    << "' at index " << index << endl;

  // Size of the combined string.
  length +=  substr_len;


  char* combined_str = (char*) malloc(sizeof(char)*length);

  // Keep track of whether the substring has already been inserted.
  bool substr_inserted = false;

  // Loop the length of the combined string.
  for (int i = 0; i < length- 1; i++) {

    // Before the insertion point, just copy over the original string
    if (i < index) 
      *(combined_str + i) = *(str + i);
    
    // Substring needs to be injected
    else if (i >= index && substr_inserted == false) {

      // Loop over the substring's length
      for (int j = 0; j < substr_len - 1; j++) {

        // "Remember" the point we started at, using i.
        *(combined_str + i + j) = *(substr + j);
      }

      // Manually bump i to where the rest of the original string goes.
      i += substr_len-2;
      substr_inserted = true;

    } else 

      // Copy in the remaining portion of the original string.
      *(combined_str + i) = *(str + i - substr_len + 1);
    
  }

  cout << "The new string is: " << combined_str << endl;
  
  return combined_str;
}

char* append(char* str, int orig_len) {

  cout << "Enter the string you would like to append." << endl;
  int append_len;
  char* append_string = get_string(append_len);
  cout << append_string << " will be appended to " << str << endl;

  orig_len += append_len;
  char* new_string = (char*) malloc(sizeof(char) * orig_len);
 
  int j = 0; // Tracks position in append_string.
  for (int i = 0; i < orig_len-1; i++) {
    
    if (i < orig_len-append_len) {
      if (*(str+i)!='\0')
        *(new_string + i) = *(str + i);
      else
        *(new_string + i) = ' ';
    } else {
      *(new_string + i) = *(append_string + j++);
    }

  }
  cout << "The new string is: " << new_string << endl;

  return new_string;
}



char* replace(char* str, int length) {
  
  cout << "Enter the substring you would like to replace: ";
  char* existing;
  int existing_len;
  existing = get_string(existing_len);

  cout << "What should it be replaced by? ";
  char* specified;
  int specified_len;
  specified = get_string(specified_len);


  int existing_index;
  existing_index = search(str, length, existing, existing_len);
  
  if (existing_index == -1) {
    cout << "That string was not found in the working string." << endl;
    return str;
  }

  length = length - existing_len + specified_len;
  char* new_str = (char*) malloc(sizeof(char) * length);

  bool specified_string_added = false;
  int orig = 0;

  // Loop over the length of the new string
  for (int i = 0; i < length; i++) {

    // Identical up to the substring's index.
    if (i < existing_index) {

      // Throw away premature null terms
      if (*(str+orig)!='\0') *(new_str + i) = *(str + orig++);

    } else if (i >= existing_index && specified_string_added == false) {

      // Loop over the replacement string's length.
      for (int j = 0; j < specified_len; j++) {

        // Again, throw away null terms
        if(*(specified+j) != '\0') {

          // The next position in newstr is from the replacement str
          *(new_str + i +j) = *(specified + j); 
        }
      }

      // Magic
      orig += specified_len-3;

      // Magic
      i += specified_len-2;

      // Leave this horrid loop forever
      specified_string_added = true;

    } else {

      // Continue adding the original string
      *(new_str + i) = *(str + orig++);
    }
  }

  cout << "The new string is: " << new_str << endl;
  return new_str;
}

char* del(char* str, int length) {

  cout << "Enter the substring you would like to delete: ";
  char* substr;
  int substr_len;
  substr = get_string(substr_len);

  int found_index;
  found_index = search(str, length, substr, substr_len);

  if (found_index == -1) {
    cout << "Substring not found in working string. No changes made." << endl;
    return str;
  }

  length = length - substr_len+1;
  char* new_str = (char*) malloc(sizeof(char) * length);

  bool substr_removed = false;
  int orig=0;

  // Loop over the length of the shortened string.
  for(int i=0; i<length; i++) {

    // Skip some letters when we get to the substr to remove.
    if (i >= found_index && substr_removed == false) {

      // Skip substr_len letters in the original string.
      orig += substr_len-1;
      
      // Run this iteration again
      i-=1;
      
      // But note that the substring was already removed.
      substr_removed = true;

      // Copy everything that's not a null term
    } else if(*(str + orig) != '\0') {

      // The pointer into the original string is fixed by the above condition
      *(new_str+i) = *(str + orig++);
    }
  }

  cout << "The working string is now: "<<new_str<<endl;
  return new_str;
}

