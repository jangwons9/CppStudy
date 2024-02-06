#include <iostream>
#include <utility>

// overloading = defining multiple functins with same function name by using different parameter types
// overriding  = inheritence 걔념 where derived class function implements the base function( though must have same retunrn type and paramter)


template <typename T>
class Entity
{

private:
T* m_ptr;

public:

//basic constructor
Entity(T* ptr = nullptr)
    :m_ptr(ptr)
{    
    std::cout << "haha" <<std:: endl;
}

~Entity(){
    delete m_ptr;
    std::cout << "haha" <<std:: endl;
}
// Move constructor(overloading)
	// Transfer ownership of a.m_ptr to m_ptr
	Entity(Entity&& a) noexcept // rvalue reference take only rvalue argument
		: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr; 
	}

//copy constructor
    Entity(const Entity& a)
    // shallow copy    :m_ptr(a.m_ptr)
    {//deep copy
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

//copy assignment
Entity& operator=(const Entity& a){
    if(&a == this){
        return *this;
    }
    // release any memory it was holdiong
    delete m_ptr;
    //deep copy
    m_ptr = new T;
    *m_ptr = *a.m_ptr;

    return *this; // return a reference to the current object no use though
    // the returned refernce actually useless
}

//move assignment 
// transfer ownership of a.m_ptr to m_ptr
Entity& operator=(Entity&& a) noexcept
{
    // Self-assignment detection
		if (&a == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr; 

		return *this;

}

    T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};



Entity <Resource> generateResource()
{
	Entity <Resource> res = new Resource ; // new Resource is rvalue while res is an lvalue
	return res; // this return value will invoke the move constructor
    // the res is actually an lvalue(an object with a type
    // but compiler treats it as a rvlaue and perform move constructor

    //std::move *****
    // return std::move(res) makes lvalue cast to rvalue reference for the compilerrr

}


int main(){
// rvalue refernce variables are lvalues/other 
    // Basic constructor
    Entity<Resource> mainres;

    // Move constructor
    Entity<Resource> mainres_move;
    

    //Copy constructor
    Entity<Resource> mainres_copy = generateResource();
        //Resource acquired (during generateResource)
        //haha
        //Resource acquired (due to copy constructor)
     
    //Move Assignment
    Entity<Resource> mainres_move_assignment;
    mainres_move_assignment = generateResource(); //this line invokes move assignment only
        // *** there is a temporary object created from return res; where res is transferd to that temporary object and since its temporary, it invokes from rvalue reference
        // the resource from temporary object is then assigned to mainres

        // mainres = (std::move(generateResource()) for std::vmoe****
	return 0;
}






