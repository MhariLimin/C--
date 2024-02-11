#include <iostream>
using namespace std;

#define MAX 10


class Queue
{
    private:
        int input[MAX];
        int top;
        int locate(int num);
    public:
        void makenull()
        {
            top = 0;
        }
        void enqueue(int num);
        void dequeue();
        void display();
        bool isFull();
        bool isEmpty();

};

void Queue::enqueue(int num)
{
    int s;
	if (isFull())
	{
		cout << "Queue Overflow" <<endl;
		system("pause");
	}
	else
    {
            s = locate(num);
            if(s>=0)
            {
              cout<<"\n\t\t\t\t\t  Duplicate Queue No. Found.\n\t\t\t\t\t  ";
              system("pause");
            }
        else
        {
            input[top] = num;
            top++;
			cout << "\n\t\t\t\t\t  Number successfully queued!\n\t\t\t\t\t  ";
			system("pause");
        }
    }
}

void Queue::dequeue()
{
	if (isEmpty())
	{
		cout << "Queue is empty" <<endl;
		system("pause");
	}
	else
	{
		for (int i = 0; i < top; i++)
		{
			input[i] = input[i+1];
		}
		top--;
	}
}

void Queue::display()
{
	system("cls");
	if (isEmpty())
	{
		cout << "Queue is empty" <<endl;
		system("pause");
	}
	else
    {
        cout<<"\n\t\t\t\t\t\t  QUEUE ENTRY LIST\n";
        cout<<"\t\t\t\t\t_____________________________________\n";
        for (int i = 0; i < top; i++)
        {
            cout<<"\n\t\t\t\t\t\t  " << i+1 << ".) " << input[i] <<endl;
        }
        cout<<"\t\t\t\t\t_____________________________________\n";
        cout<<"\n\t\t\t\t\t  ";
        system("pause");
    }
}

int Queue::locate(int num) //locates the inputted data them compares it to the list
{

    int i;
    //int first;


    for (i=0;i<=top;i++)
    {
        if (input[i]==num)
            return i;
    }
    return -1;
}

bool Queue::isFull()
{
	return (top==MAX);
}

bool Queue::isEmpty()
{
	return (top==0);
}


int menu()
{
    int choice;
    system("cls");
    cout<<"\n\t\t\t\t\t\t   QUEUE MENU\n";
    cout<<"\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout<<"\t\t\t\t\t   1. Enqueue\n";
    cout<<"\t\t\t\t\t   2. Dequeue\n";
    cout<<"\t\t\t\t\t   3. Display\n";
    cout<<"\t\t\t\t\t   4. Exit\n";
    cout<<"\t\t\t\t\t_________________________________\n";
    cout<<"\n\t\t\t\t\t Please Select (1-4): ";
    cin>>choice;
    return (choice);
}
int main(void)
{
    int num;
	Queue q;
	q.makenull();


	while (true)
	{
		system("cls");

		switch (menu())
		{
		case 1:
		    system("cls");
		    cout<<"\n\t\t\t\t\t      INSERT NUMBER TO ENQUEUE\n";
            cout<<"\t\t\t\t\t_____________________________________\n";
			cout << "\n\t\t\t\t\t  Input number to enqueue: ";
			cin >> num;
			cin.get();
			cout<<"\t\t\t\t\t_____________________________________\n";
			q.enqueue(num);
			break;

		case 2:
			q.dequeue();
            cout << "\n\t\t\t\t\t Top entry successfully dequeued!\n\t\t\t\t\t ";
			system("pause");
			break;

		case 3:
			q.display();
			break;

		case 4:
			exit(0);
			break;

		default:
			cout <<"\n\t\t\t\t\t Please pick from 1-4 only..\n\t\t\t\t\t ";
			system("pause");
		}

  	}
}
