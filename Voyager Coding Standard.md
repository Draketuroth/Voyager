# Voyager Coding Standard

During my few years of programming, I have realized the importance of having a code standard. 
The Voyager Engine is no exception, so I decided to share it here on my repository. I have a feeling this will be updated
as I go along, so expect more content in the future. Feel free to come with suggestions
or poke me with something flashier :)

## 1. Variable names
All variables should be written in snake case.

```
class Example {
  public:
      double a_fantastic_double;
}
```

## 2. Constants and macro names
Any constants and macros should be written in all caps.

```
#define IMPORTANT_MACRO_IS_ON

const int SUPER_IMPORTANT_CONSTANT = 1
int number;

#if IMPORTANT_MACRO_IS_ON
    number = SUPER_IMPORTANT_CONSTANT;
#else
    number = 2;
#endif
```

## 3. Functions and method names
Functions and methods should use mixed camel case with first letter always lower case.

```
class Example {
  public:
      void myMethod();
}

void myFunction();
```

## 4. Struct and class names
Structs and classes use mixed camel case with first letter always upper case. 

```
class Example {
  
}

struct AnotherExample{

}
```

## 5. Private data members
Private datamembers should use underline prefix, which I find preferable compared to writing "this->". 

```
class Example {
  private:
      int _my_private_integer;
      string _name;
}
```

## 6. Braces around each expression, even if it is only one line
This can quickly turn into a religious debate and my reason for doing this is simply to be consistent. 

```
bool status = true;

if(status == true){
    cout << "This is just one line of code, but I still use a closing brace" << endl;
}
```

## 7. Use const keyword whenever something is not intended to be changed
This one speaks for itself and has always been important. Yet I tend to forget it from time to time anyway, so I try to enforce it on myself. 

```
class Example {
  public:
      Example(const Example&);
      
      void writeExampleData() const;
      void addExampleData(const char* category, float number);
      
}
```

## 8. Comments must be punctuated, just like sentences
Maybe one of the most important rules is to always punctuate your comments, with some exception of file header comments. This also has to do with being consistent, but some would also
argue that it looks more professional. 

```
// This is a comment, but I most not forget to punctuate the comment. 

/* 
I find it equally important over several lines.
In fact, we should treat our sentences with respect. 
*/
```
