#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TEMP : virtual public ICGReferenceCount
{
public:
	static	int		m_iCount;
public:
	TEMP(int a) : value(a){ ++m_iCount;}
	~TEMP()	{ --m_iCount;}
public:
	int	value;
};

int TEMP::m_iCount	 = 0;

namespace CGDContainers_UnitTest
{		
	TEST_CLASS(UnitTest_array)
	{
	public:
		// Initialize) 
		TEST_METHOD_INITIALIZE(Initialization) 
		{
		}

		TEST_METHOD_CLEANUP(CleanUp) 
		{
		}

		// 1) CGD::array push_back and pop_back
		TEST_METHOD(Test_Container_array_push_back_pop_back)
		{
			CGD::array<int, 10>	temp;


			temp.push_back(10);
			temp.push_back(120);
			temp.push_back(70);
			temp.push_back(20);
			temp.push_back(30);

			temp.pop_back();
			temp.pop_back();
			temp.pop_back();
			temp.pop_back();
			temp.pop_back();
		}

		// 2) CGD::array push_back and pop_front
		TEST_METHOD(Test_Container_array_push_back_pop_front)
		{
			// Declare) 
			CGD::array<int, 10>	temp;

			// 1) push_back
			temp.push_back(10);
			temp.push_back(120);
			temp.push_back(70);
			temp.push_back(20);
			temp.push_back(30);
			Assert::IsTrue(temp.front()==10);

			// 2) pop_front
			temp.pop_front();	Assert::IsTrue(temp.front()==120);
			temp.pop_front();	Assert::IsTrue(temp.front()==70);
			temp.pop_front();	Assert::IsTrue(temp.front()==20);
			temp.pop_front();	Assert::IsTrue(temp.front()==30);
			temp.pop_front();	Assert::IsTrue(temp.empty());
		}

		// 2) CGD::array push_back and pop_front
		TEST_METHOD(Test_Container_array_push_front_pop_back)
		{
			// Declare) 
			CGD::array<int, 10>	temp;

			// 1) push_back
			temp.push_front(10);
			temp.push_front(120);
			temp.push_front(70);
			temp.push_front(20);
			temp.push_front(30);
			Assert::IsTrue(temp.back()==10);

			// 2) pop_front
			temp.pop_back();	Assert::IsTrue(temp.back()==120);
			temp.pop_back();	Assert::IsTrue(temp.back()==70);
			temp.pop_back();	Assert::IsTrue(temp.back()==20);
			temp.pop_back();	Assert::IsTrue(temp.back()==30);
			temp.pop_back();	Assert::IsTrue(temp.empty());
		}

		// 2) CGD::array push_back and pop_front
		TEST_METHOD(Test_Container_array_push_front_erase_begin)
		{
			// Declare) 
			CGD::array<int, 10>	temp;

			// 1) push_back
			temp.push_front(10);
			temp.push_front(120);
			temp.push_front(70);
			temp.push_front(20);
			temp.push_front(30);
			Assert::IsTrue(temp.front()==30);

			// 2) pop_front
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()==20);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()==70);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()==120);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()==10);
			temp.erase(temp.begin());	Assert::IsTrue(temp.empty());
		}

		// 3) CGD::array push_back and pop_front
		TEST_METHOD(Test_Container_array_push_front_erase_end)
		{
			// Declare) 
			CGD::array<int, 10>	temp;

			// 1) push_back
			temp.push_front(10);
			temp.push_front(120);
			temp.push_front(70);
			temp.push_front(20);
			temp.push_front(30);
			Assert::IsTrue(temp.back()==10);

			// 2) pop_front
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==120);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==70);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==20);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==30);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.empty());
		}

		// 3) CGD::array push_back and pop_front
		TEST_METHOD(Test_Container_array_push_front_erase_begin_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp;

			// 1) push_back
			temp.push_front(NEW<TEMP>(10));
			temp.push_front(NEW<TEMP>(120));
			temp.push_front(NEW<TEMP>(70));
			temp.push_front(NEW<TEMP>(20));
			temp.push_front(NEW<TEMP>(30));
			Assert::IsTrue(temp.front()->value==30);

			// 2) pop_front
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()->value==20);	Assert::IsTrue(TEMP::m_iCount==4);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()->value==70);	Assert::IsTrue(TEMP::m_iCount==3);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()->value==120);	Assert::IsTrue(TEMP::m_iCount==2);
			temp.erase(temp.begin());	Assert::IsTrue(temp.front()->value==10);	Assert::IsTrue(TEMP::m_iCount==1);
			temp.erase(temp.begin());	Assert::IsTrue(temp.empty());				Assert::IsTrue(TEMP::m_iCount==0);

			Assert::IsTrue(temp.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}

		// 4) CGD::array insert and pop_front
		TEST_METHOD(Test_Container_array_insert_erase_end)
		{
			// Declare) 
			CGD::array<int, 10>	temp;

			// 1) push_back
			temp.insert(temp.begin(), 10);
			temp.insert(temp.begin(), 120);
			temp.insert(temp.begin(), 70);
			temp.insert(temp.begin(), 20);
			temp.insert(temp.begin(), 30);
			Assert::IsTrue(temp.back()==10);

			// 2) pop_front
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==120);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==70);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==20);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()==30);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.empty());
		}

		// 4) CGD::array insert and pop_front_CGPTR
		TEST_METHOD(Test_Container_array_insert_erase_end_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp;

			// 1) push_back
			temp.insert(temp.begin(), NEW<TEMP>(10));
			temp.insert(temp.begin(), NEW<TEMP>(120));
			temp.insert(temp.begin(), NEW<TEMP>(70));
			temp.insert(temp.begin(), NEW<TEMP>(20));
			temp.insert(temp.begin(), NEW<TEMP>(30));
			Assert::IsTrue(temp.back()->value==10);

			// 2) pop_front
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()->value==120);	Assert::IsTrue(TEMP::m_iCount==4);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()->value==70);		Assert::IsTrue(TEMP::m_iCount==3);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()->value==20);		Assert::IsTrue(TEMP::m_iCount==2);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.back()->value==30);		Assert::IsTrue(TEMP::m_iCount==1);
			temp.erase(temp.end()-1);	Assert::IsTrue(temp.empty());				

			Assert::IsTrue(temp.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}

		// 4) CGD::array insert and pop_front_CGPTR
		TEST_METHOD(Test_Container_array_insert_clear_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp;

			// 1) push_back
			temp.insert(temp.begin(), NEW<TEMP>(10));
			temp.insert(temp.begin(), NEW<TEMP>(120));
			temp.insert(temp.begin(), NEW<TEMP>(70));
			temp.insert(temp.begin(), NEW<TEMP>(20));
			temp.insert(temp.begin(), NEW<TEMP>(30));
			Assert::IsTrue(temp.back()->value==10);

			// 2) clear
			temp.clear();	
			
			Assert::IsTrue(temp.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}
		
		// 4) CGD::array insert and pop_front_CGPTR
		TEST_METHOD(Test_Container_array_insert_erase_range_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp;

			// 1) push_back
			temp.insert(temp.end(), NEW<TEMP>(10));
			temp.insert(temp.end(), NEW<TEMP>(120));
			temp.insert(temp.end(), NEW<TEMP>(70));
			temp.insert(temp.end(), NEW<TEMP>(20));
			temp.insert(temp.end(), NEW<TEMP>(30));
			Assert::IsTrue(temp.back()->value==30);

			// 2) clear
			temp.erase(++temp.begin(), --temp.end());
			
			Assert::IsTrue(TEMP::m_iCount==2);
			Assert::IsTrue(temp.size()==2);
			Assert::IsTrue(temp.front()->value==10);
			Assert::IsTrue(temp.back()->value==30);

			temp.erase(temp.begin());
			temp.erase(temp.end()-1);
			
			Assert::IsTrue(temp.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}

		// 4) CGD::array insert and pop_front_CGPTR
		TEST_METHOD(Test_Container_insert_ranged_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp1;
			CGD::array<CGPTR<TEMP>, 10>	temp2;

			// 1) push_back
			temp1.push_back(NEW<TEMP>(1));
			temp1.push_back(NEW<TEMP>(2));
			temp1.push_back(NEW<TEMP>(3));
			temp1.push_back(NEW<TEMP>(4));
			temp1.push_back(NEW<TEMP>(5));

			// 2) push_back
			temp2.push_back(NEW<TEMP>(10));
			temp2.push_back(NEW<TEMP>(11));
			temp2.push_back(NEW<TEMP>(12));
			temp2.push_back(NEW<TEMP>(13));
			temp2.push_back(NEW<TEMP>(14));

			// 3) Insert Ranged
			temp1.insert(++temp1.begin(), temp2.begin(), temp2.end());
			
			// Check)
			Assert::IsTrue(TEMP::m_iCount==10);
			Assert::IsTrue(temp1.size()==10);
			Assert::IsTrue(temp2.size()==5);
			Assert::IsTrue(temp1[0]->value==1);
			Assert::IsTrue(temp1[1]->value==10);
			Assert::IsTrue(temp1[2]->value==11);
			Assert::IsTrue(temp1[3]->value==12);
			Assert::IsTrue(temp1[4]->value==13);
			Assert::IsTrue(temp1[5]->value==14);
			Assert::IsTrue(temp1[6]->value==2);
			Assert::IsTrue(temp1[7]->value==3);
			Assert::IsTrue(temp1[8]->value==4);
			Assert::IsTrue(temp1[9]->value==5);

			// 4) Clear
			temp1.clear();
			Assert::IsTrue(TEMP::m_iCount==5);
			temp2.clear();
			
			// Check)
			Assert::IsTrue(temp1.size()==0);
			Assert::IsTrue(temp2.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}

		// 4) CGD::array insert and pop_front_CGPTR
		TEST_METHOD(Test_Container_insert_N_CGPTR)
		{
			// Declare) 
			CGD::array<CGPTR<TEMP>, 10>	temp;

			// 1) push_back
			temp.push_back(NEW<TEMP>(1));
			temp.push_back(NEW<TEMP>(2));
			temp.push_back(NEW<TEMP>(3));
			temp.push_back(NEW<TEMP>(4));
			temp.push_back(NEW<TEMP>(5));
			
			// 2) Insert N
			temp.insert(++temp.begin(), 5, NEW<TEMP>(10));
			
			// Check)
			Assert::IsTrue(TEMP::m_iCount==6);
			Assert::IsTrue(temp.size()==10);
			Assert::IsTrue(temp[0]->value==1);
			Assert::IsTrue(temp[1]->value==10);
			Assert::IsTrue(temp[2]->value==10);
			Assert::IsTrue(temp[3]->value==10);
			Assert::IsTrue(temp[4]->value==10);
			Assert::IsTrue(temp[5]->value==10);
			Assert::IsTrue(temp[6]->value==2);
			Assert::IsTrue(temp[7]->value==3);
			Assert::IsTrue(temp[8]->value==4);
			Assert::IsTrue(temp[9]->value==5);

			// 3) Clear
			temp.clear();
			
			// Check)
			Assert::IsTrue(temp.size()==0);
			Assert::IsTrue(TEMP::m_iCount==0);
		}
	};
}


