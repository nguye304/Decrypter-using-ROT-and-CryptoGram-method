//ASSIGNMENT 1 DUE SEPTEMBER 22 2016
//KEVIN NGUYEN
//CS211
//This program is suppose to get input from the user and help them decrypt or encrypt using ROT method and Cryptogram method

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
//--------------------Prototypes--------------------------
int  getInfo();
vector<string> getWords();
vector<string> encryptingWithROT(vector <string> words);
void print(vector<string>V);//to check work
string changeToLowerCase(string w);
int getRotNumber();
string encryptingROT(int rotNum,string words);
string decryptingROT(int rotNum,string aWord);
vector<string> decryptingWithROT(vector <string> words);
vector<string> encryptingWithCrypto(vector <string> words);
string encryptingCrypto(string key,string aWord);
vector<string> decryptingWithCrypto(vector<string>words);
string decryptingCrypto(string key,string aWord);//decryption of cryptogram
string getKey();//function to get the cryptogram key
void placeInFile(string, vector<string> V);//function to place into output files

//--------------------------------------------------------
int main()
{
  
  
  int choice=getInfo();//the users choice

  
  vector<string>words=getWords();
  vector<string>decryptedROT;
  vector<string>encryptedROT;
  vector<string>decryptedCrypto;
  vector<string>encryptedCrypto;

  
  if (choice == 1)//rot encryption
    {
      encryptedROT=encryptingWithROT(words);//the word after it has been encrypted with ROT method
      print(encryptedROT);
      cout<<endl<<endl;
    }
  else if (choice ==2)//crypto encrypt
    {
    encryptedCrypto=encryptingWithCrypto(words);
      print(encryptedCrypto);
      placeInFile("encrypt2.txt",encryptedCrypto);
    }
  else if (choice ==3)//rot decrypt
    {
      encryptedROT=encryptingWithROT(words);
      decryptedROT=decryptingWithROT(encryptedROT);//the word after it has been decrypted with ROT METHOD
      print(decryptedROT);
      placeInFile("decrypt1.txt",decryptedROT);
  
    }
  else if(choice==4)//Cryptogram decryption
    {
      encryptedCrypto=encryptingWithCrypto(words);
      decryptedCrypto=decryptingWithCrypto(encryptedCrypto);
      print(decryptedCrypto);
      placeInFile("decrypt2.txt",decryptedCrypto);
    }
  else ;
  
  return 0;
}

//Function to check work--------------------------------------------
void print(vector<string>V)
{
  for(int i=0; i<V.size();i++)
    {
      cout<<V[i]<<" ";
      //      cout<<endl;
    }
}


//Functions to get the words from the text file
vector<string> getWords()
{
  vector<string>words;//vector that holds each word
  string X;//a letter
  ifstream fin;
  fin.open("origin.txt");
  while(fin>>X)
    {
      X=changeToLowerCase(X);//function that changes upper to lower
      words.push_back(X);
    }
  return words;  
}

string changeToLowerCase(string w)
{
  for(int i=0; i<w.size(); i++)
    {
      w[i]=tolower(w[i]);
    } 
  return w;
}


void placeInFile(string filename, vector<string> V)//function to place into output files
{
  //declare a output file
  ofstream output;
  
  output.open(filename.data());
  
   output << "The title of this file is " << filename << endl << endl;
   
   
  for(int i= 0 ; i < V.size(); i++)
    {
      
      output <<V[i]<<" ";
      
    }
  
 
  output.close(); //close file

}





//ROT 
//ENCRYPTING==========================================================

vector<string> encryptingWithROT(vector <string> words)
{
  vector<string>B;//vector that holds the finsihed encrypted word
  string enWord;//a string variable that holds 1 word
  int RotNum = getRotNumber();
  //  cout<<RotNum<<endl;// to check
  
  for (int i=0; i<words.size();i++)
    {
      enWord=encryptingROT(RotNum,words[i]);
      B.push_back(enWord);
      
    }  
  return B;
}

int getRotNumber()
{
  int num;
  cout<<"Please insert Desired ROT number: ";
  cin>>num;
  
  return num;
}


string encryptingROT(int rotNum,string aWord)
{
  for (int i=0; i<aWord.size();i++)
    {
      if (aWord[i]<'a' || aWord[i]> 'z')
	{
	  aWord[i]=aWord[i];
	}
      else
	{
	  int x=aWord[i]-'a';
	  x=x+rotNum;
	  aWord[i]=aWord[i]+rotNum;
	  if (x>25)
	    {
	      x=x-26;
	      x=x+'a';
	      aWord[i]=x;
	    }
	}  
    } //FOR LOOP END 
  

  return aWord;
}

//==========================================================================


//DECRYPTING ROT============================================================
vector<string> decryptingWithROT(vector <string> words)
{
  vector<string>A;//vector that holds the finsihed encrypted word
  string deWord;//a string variable that holds 1 word
  int RotNum = getRotNumber();
  cout<<RotNum<<endl;// to check
  
  for (int i=0; i<words.size();i++)
    {
      deWord=decryptingROT(RotNum,words[i]);
      A.push_back(deWord);
      
    }
  return A;
}

string decryptingROT(int rotNum,string aWord)
{
  
  for (int j=0; j < aWord.size(); j++)
    {
      if (aWord[j] <'a' || aWord[j]> 'z')
        {
          aWord[j]=aWord[j];
        }
      else
        {
          int x=aWord[j]-'a';
          x=x-rotNum;
          aWord[j]=aWord[j]-rotNum;
          if (x<0)
            {
              x=x+26;
              x=x+'a';
              aWord[j]=x;
            }
        }
    }
  return aWord;
    
}
//============================================================================
vector<string> encryptingWithCrypto(vector <string> words)
{
  vector<string>C;//vector that holds the finsihed encrypted word
  string enWord;//a string variable that holds 1 word
  string key = getKey();

  for (int i=0; i<words.size();i++)
    {
    enWord=encryptingCrypto(key,words[i]);
    C.push_back(enWord);
    }
    return C;
}


string getKey()
{
  string key;//vector that holds each word
  ifstream fin;
  fin.open("crypto.txt");
  fin>>key;
  cout<<key<<endl;
  return key;
}

string encryptingCrypto(string key,string aWord)
  {   
    string eWord;//encrypted word
    int letter; 
    eWord=aWord;
    for (int k=0; k<eWord.size();k++)
      {
	letter=eWord[k];
	letter=tolower(letter);
	if(letter < 'a' || letter >'z')
	  eWord[k]=letter;
	else
	  {
	    int index=letter-'a';
	    eWord[k]=key[index];
	  }
      }
    
    return eWord;
  }


vector<string> decryptingWithCrypto(vector <string> words)
{
  vector<string>D;//vector that holds the finsihed encrypted word
  string deWord;//a string variable that holds 1 word
  string key = getKey();
  for (int i=0; i<words.size();i++)
    {
      deWord=decryptingCrypto(key,words[i]);
      D.push_back(deWord);
    }
  return D;
}


string decryptingCrypto(string key,string aWord)
{
  bool found=false;
  string dWord="";//decrypted word
  int letter=0;
  int x=0;
  int index=0;
  string key2="abcdefghijklmnopqrstuvwxyz";
  dWord=aWord;
  for (int k=0; k<dWord.size();k++)//reead whole word char by char
    {
      found=false;
      x=0;
      letter=dWord[k];
      letter=tolower(letter);
      
      if(letter < 'a' || letter >'z') //check if punctuation
	dWord[k]=letter; //do nothing if punctuation

      else //letter is in the alphabet
	{
	  for(int i=0; i<key.size();i++) // compares to crypto key
	    {
	      while(!found && x<key.size()) //looping through crypto key
		{
		  if(letter == key[x])//searching for letter
		    {
		      index=x; //position in alphabet key
		      letter=key2[index]; //letter is equal to whatever alphabet char is in that index
		      
		      dWord[k]=letter;		 
		      found=true;//if found break out
		    } 
		  x++;
		} //end while loop
	    
	    }//for loop
	  
	}//else loop end
    }
  

  return dWord;

}
       







int  getInfo()
{
  int final;//the final decision
  string ans;//the answer of the user
  cout<<"Do you want to do an Encryption or Decryption?"<<endl;
  cin>>ans;
  if (ans=="Encryption" || ans =="encryption")
    {//being of if
      cout<<"Do you want to use ROT method or Cryptogram method?"<<endl;
      cin>>ans;
      
      if (ans=="ROT" || ans== "rot" || ans =="Rot")  
	{
	  final=1;//choice 1 is rot ENCRYPTING
	}
      else if (ans=="Cryptogram" || ans=="cryptogram")
	{
	  final=2;//choice 2 is cryptogram ENCRYPTING
	}
    }//end of if 
  
  else if (ans=="Decryption" || ans == "decryption")
    {//being else if
      cout<<"Are you using ROT method or Cryptogram medthod?"<<endl;
      cin>>ans;      
      if (ans=="ROT" || ans== "rot" || ans =="Rot")
        {
          final=3;//choice 3 is DECRYPTING with ROT 
	  }
      else if (ans=="Cryptogram" || ans=="cryptogram")
        {
          final=4;//choice 4 is a DECRYPTING with cryptogram
        }	
    }//end of elseif
  else 
    cout<<"Invalid Choice. Please choose Encryption or Decryption."<<endl;
  
  return final;
  
}  



									 
