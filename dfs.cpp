#include <iostream>

using namespace std;
#define WIDTH 3
#define HEIGHT 3

//******************** WORKING BRAKA DFS *******
class State
{

    int robX,robY;
    int free[WIDTH][HEIGHT];
    int pathSize=0;
    string *path=NULL;

    int numb [3][3];



public:
    State()
    {
        /*
        numb[0][0]=7;
        numb[0][1]=6;
        numb[0][2]=1;
        numb[1][0]=0;
        numb[1][1]=3;
        numb[1][2]=2;
        numb[2][0]=8;
        numb[2][1]=5;
        numb[2][2]=4;
        robX=1;
        robY=0;*/
    }
    State(int X, int Y)
    {
        robX=X;
        robY=Y;
        for (int i=0; i<WIDTH; i++)
            for (int j=0; j<HEIGHT; j++)
                free[i][j]=true;

    }

    State (const State &old)
    {

        robX = old.robX;
        robY = old.robY;
        path = old.path;
        pathSize = old.pathSize;
        for (int i=0; i<WIDTH; i++)
        {
            for (int j=0; j<HEIGHT; j++)
                free[i][j]=old.free[i][j];
        }
    }
    void print()
    {
        cout<< "Path: ";
        for(int j=0; j<pathSize; j++)
        {
            cout<< path[j];
        }
        cout<<endl;
    }

    bool equals (State s)
    {
        if (robX==s.robX && robY==s.robY)
            return true;
        return false;
    }

    bool equals2(State s)
    {

        int pl=0;
        for(int i=0; i<WIDTH; i++)
        {
            for (int j=0; j<HEIGHT; j++)
            {
                if(numb[i][j]==s.numb[i][j])
                    pl++;
            }
        }
        if(pl==9)
            return true;
        return false;
    }

    void setFree(int i, int j, bool f)
    {
        free[i][j] = f;
    }
    bool isFree(int x,int y)
    {
        return free[x][y] ;
    }
    int getY()
    {
        return robY;
    }
    int getX()
    {
        return robX;
    }
    void setX(int x)
    {
        robX = x;
    }
    void setY(int y)
    {
        robY = y;
    }

    void addAction (string a)
    {
        string *temp;
        int i;
        pathSize++;
        temp = new string[pathSize];
        for(i=0; i<pathSize-1; i++)
            temp[i]=path[i];
        temp[i]=a;
        delete path;
        path=temp;
    }
};

class node //parent and children
{
public:
    State data;
    node *next;
};

class Stack //
{
protected:
    node *head;
public:

    Stack()
    {
        head=NULL;
    }
    ~Stack()
    {
        node *t;
        while (head!=NULL)
        {
            t=head;
            head=head->next;
            delete(t);
        }
    }
    bool push (State s)
    {
        node *a;
        a = new node;
        if (a==NULL)
            return false;
        a->data=s;
        a->next=head;
        head = a;
        return true;
    }
    bool pop (State &s)
    {
        if (head==NULL)
            return false;
        s=head->data;
        node *temp = head;
        head= head->next;
        delete temp;
        return true;
    }
    bool isEmpty()
    {
        return (head==NULL);
    }
};

class Set:private Stack
{
public:
    Set():Stack()
    {
    }
    bool find (State s)
    {
        node *t=head;
        while (t!=NULL)
        {
            if (t->data.equals(s))
                return true;
            t=t->next;
        }
        return false;
    }
    bool insert(State s)
    {
        if (!find(s))
            return push(s);
        return true;
    }
};


bool goUp(State s, State &n)
{
    if (s.getY()>1 && s.isFree(s.getX(),s.getY()-1))
    {
        n=s;
        n.setY(n.getY()-1);
        n.addAction("Up");
        return true;
    }
    return false;
}
bool goDown(State s, State &n)
{
    if (s.getY()<HEIGHT && s.isFree(s.getX(),s.getY()+1))
    {
        n=s;
        n.setY(n.getY()+1);
        n.addAction("Down");
        return true;
    }
    return false;
}
bool goLeft(State s, State &n)
{
    if (s.getX()>1 && s.isFree(s.getX()-1,s.getY()))
    {
        n=s;
        n.setX(n.getX()-1);
        n.addAction("Left");
        return true;
    }
    return false;
}
bool goRight(State s, State &n)
{
    if (s.getX()<WIDTH&& s.isFree(s.getX()+1,s.getY()))
    {
        n=s;
        n.setX(n.getX()+1);
        n.addAction("Right");
        return true;
    }
    return false;
}

void expand(const State &s, State* &children, int &num)
{
    State u,d,l,r;
    int i=0;
    num=0;
    if (goUp(s,u))
        num++;
    if (goDown(s,d))
        num++;
    if (goLeft(s,l))
        num++;
    if (goRight(s,r))
        num++;
    children = new State[num];
    if (goUp(s,u))
        children[i++]=u;
    if (goDown(s,d))
        children[i++]=d;
    if (goLeft(s,l))
        children[i++]=l;
    if (goRight(s,r))
        children[i++]=r;
}
bool DFS(Stack &agenda, Set &closed,const State &goal,State &solution)
{
    
}
int main()
{
    Stack agenda;
    Set closed;
    State initial(1,1);
    initial.setFree(4,1,false);
    initial.setFree(3,2,false);
    initial.setFree(4,3,false);
    State goal(5,4);
    agenda.push(initial);
    State solution;
    DFS(agenda,closed,goal,solution);
    cout<<"Solution "<<endl;
    solution.print();
    return 0;
}

