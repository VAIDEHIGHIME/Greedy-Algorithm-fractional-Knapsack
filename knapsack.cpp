#include<bits/stdc++.h>
using namespace std;
/*----------------------------------------------------Object-----------------------------------------------------*/
class object
{
   public:
	float weight;//remains as it is
	float profit;//remains as it is
	float profitbyweight;//remains as it is
	float fraction;// need to set when object is added

	object();
	void SetObject(float ,float );
	float GetWeight();
    float GetProfit();
    float GetProfitByWeight();
    float GetFraction();
    void SetFraction(float);
    void PrintObject();
};
object::object()
{
    weight=0;
    profit=0;
    profitbyweight=0;
    fraction=1;
}
void object:: SetObject(float w,float p)
{
    weight=w;
    profit=p;
    profitbyweight=profit/weight;
}
float object:: GetWeight()
{
    return(weight);
}
float object:: GetProfit()
{
    return(profit);
}
float object:: GetProfitByWeight()
{
    return(profitbyweight);
}
float object:: GetFraction()
{
    return(fraction);
}
void object::SetFraction(float f)
{
    fraction=f;
}
void object:: PrintObject()
{
    cout<<"[";
    cout<<"w:"<<weight<<"\t";
    cout<<"p:"<<profit<<"\t";
    cout<<"p/w:"<<profitbyweight<<"\t";
    cout<<"x:"<<fraction;
    cout<<"]\n";
}
/*--------------------------------------------------knapsack--------------------------------------------------------------*/
class knapsack
{

    public:
    object * obj;//pointer to array of objects
    int objIncluded;//no of objects included in the knapsack
	float capacity;//total capacity of the knapsack
	float leftSpace;//space left in the knapsack
	float profitIncluded;


	knapsack();//constructor
	float GetOccupiedSpace();
	void SetKnapsack(float,int);//set the weight of the knapsack and the max no of objects .
	float GetCapacity();//returns capacity of the knapsack
	float GetSpaceLeft();//return the left space in the knapsack
	float GetProfit();//returns profit
	void AddObject(object ,float);//adds a object to the knapsack
};
float knapsack::GetOccupiedSpace()
{
    return(capacity-leftSpace);
}
void knapsack:: AddObject(object o,float frac)
{
    obj[objIncluded].SetObject(o.GetWeight(),o.GetProfit());
    obj[objIncluded].SetFraction(frac);
    profitIncluded=profitIncluded+obj[objIncluded].GetProfit()*obj[objIncluded].GetFraction();
    leftSpace=leftSpace-obj[objIncluded].GetWeight()*obj[objIncluded].GetFraction();
    objIncluded ++;
}
knapsack::knapsack()
{
    objIncluded=0;
    capacity=0;
    leftSpace=0;
    profitIncluded=0;
}
float knapsack::GetProfit()
{
    return(profitIncluded);
}
float knapsack::GetCapacity()
{
    return(capacity);
}
float knapsack::GetSpaceLeft()
{
    return(leftSpace);
}
void knapsack::SetKnapsack(float weight,int n)
{
        capacity=weight;
        leftSpace=weight;
        obj=new object[n];
}

/*---------------------------------------------------------Helping functions-----------------------------------------------------------------------*/

/*void SwapObject(object &obj1,object &obj2)
{
    object temp;
    //swapping attribute1
    temp.weight=obj2.weight;
    obj2.weight=obj1.weight;
    obj1.weight=temp.weight;
    //swapping attribute 2
    temp.profit=obj2.profit;
    obj2.profit=obj1.profit;
    obj1.profit=temp.profit;
    //swapping attribute 3
    temp.profitbyweight=obj2.profitbyweight;
    obj2.profitbyweight=obj1.profitbyweight;
    obj1.profitbyweight=temp.profitbyweight;
    //swapping attribute 4
    temp.fraction=obj2.fraction;
    obj2.fraction=obj1.fraction;
    obj1.fraction=temp.fraction;

}*/
void SortObjects(object *obj,int n)
{
    int done=0;
    int j,i=0;
    while(done==0 && i<=n-1)
    {
        j=0;
        while(j<n-i-1)
        {
            done=1;
            if(obj[j].GetProfitByWeight()>obj[j+1].GetProfitByWeight())
            {
                // SwapObject(obj[i],obj[i+1]);
                object temp;
                //swapping attribute1
                temp.weight=obj[j+1].weight;
                obj[j+1].weight=obj[j].weight;
                obj[j].weight=temp.weight;
                //swapping attribute 2
                temp.profit=obj[j+1].profit;
                obj[j+1].profit=obj[j].profit;
                obj[j].profit=temp.profit;
                //swapping attribute 3
                temp.profitbyweight=obj[j+1].profitbyweight;
                obj[j+1].profitbyweight=obj[j].profitbyweight;
                obj[j].profitbyweight=temp.profitbyweight;
                //swapping attribute 4
                temp.fraction=obj[j+1].fraction;
                obj[j+1].fraction=obj[j].fraction;
                obj[j].fraction=temp.fraction;

                done=0;
            }
            j++;
        }
        i++;
    }
}
/*-----------------------------------------------------------Main-----------------------------------------------------------------------------*/
int main()
{
    float maxWeight,objw,objp;
    int n;
    cout<<"Creating a knapsack....\n";
    cout<<"Max Weight Capacity of Knapsack:\t";
    cin>>maxWeight;
    cout<<"No of Objects Available:\t";
    cin>>n;
    knapsack k;
    k.SetKnapsack(maxWeight,n);
    cout<<"Let us create "<<n<<" objects...\n";
    object o[n];
    for(int i=0;i<n;i++)
    {
        cout<<"weight"<<"["<<i+1<<"]:"<<"\t";
        cin>>objw;
        cout<<"profit"<<"["<<i+1<<"]:"<<"\t";
        cin>>objp;
        o[i].SetObject(objw,objp);
    }
    for(int i=0;i<n;i++)
    {
        cout<<"Obj["<<i+1<<"]:: ";
        o[i].PrintObject();
    }
    //till here we all got the input from the user.
    //now we need to sort the objects according to the profit by weight ratio.
    //function for sorting objects according to p/w.
    SortObjects(o,n);
    cout<<"Sorted by profit/weight ratio\n";
    for(int i=0;i<n;i++)
    {
        cout<<"Obj["<<i+1<<"]:: ";
        o[i].PrintObject();
    }
    //now what we need to do is include the objects in the knapsack starting with the highest ratio
    int i;
    for( i=n-1;i>=0;i--)
    {
        if( k.GetOccupiedSpace()+o[i].GetWeight()<=k.GetCapacity())
        {

                k.AddObject(o[i],1);
                o[i].SetFraction(0);

        }
        else
        {

                float fraction=(k.GetSpaceLeft())/o[i].GetWeight();
                k.AddObject(o[i],fraction);
                o[i].SetFraction(1-fraction);
                break;
        }
    }
    cout<<"My Knapsack....\n";
    cout<<"Knapsack Profit:\t"<<k.GetProfit()<<endl;
    //cout<<"Knapsack left Capacity:\t"<<k.GetSpaceLeft()<<endl;
    cout<<"The objects in the Knapsack Are.....\n";
    for(int i=0;i<n;i++)
    {
        if(k.obj[i].GetFraction()!=0 && k.obj[i].GetWeight()!=0 )
        {
            cout<<"Obj["<<i+1<<"]:: ";
            k.obj[i].PrintObject();
        }
    }
    cout<<"left objects...\n";
    for(int i=0;i<n;i++)
    {
       if(o[i].GetFraction()!=0)
        {
             cout<<"Obj["<<i+1<<"]:: ";
            o[i].PrintObject();
        }
    }

    return(0);
}



