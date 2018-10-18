//For each of linear probing, quadratic probing,
//and double hashing do the following:

//Hash 900 random numbers into a table of length 1009
//using open addressing then add 50 more random integers
//currently not in the table to the table while counting
//the total number of probes for the last 50.  Use the hash
//functions given in exercise 11.4-1.

#include <cstdlib>
#include <iostream>

int size = 1009;
int * table = NULL;
int EMPTY = 0;
int DELETED = -1;
int FAILED = -2;
int collisions = 0;

//hash functions

int linearHash(int key, int i)
{
  //h(k,i) = (h'(k) + i) mod m
  return (key + i) % size;
}

int quadraticHash(int key, int i)
{
  //h(k,i) = (h'(k) + c1*i + c2*i) mod m
  int c1 = 1;
  int c2 = 3;
  return (key + c1*i + c2*i) % size;
}

int doubleHash(int key, int i)
{
  //h(k,i) = (h1(k) + i*h2(k)) mod m
  return ((key % size) + i * (1 + (key % (size - 1)))) % size;
}

//insert functions

int linearInsert(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = linearHash(value, i);

    if(table[key] == EMPTY || table[key] == DELETED)
    {
      table[key] = value;
      return key;
    }

    collisions++;

    i++;
  }

  return FAILED;
}

int quadraticInsert(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = quadraticHash(value, i);

    if(table[key] == EMPTY || table[key] == DELETED)
    {
      table[key] = value;
      return key;
    }

    collisions++;

    i++;
  }

  return FAILED;
}

int doubleInsert(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = doubleHash(value, i);

    if(table[key] == EMPTY || table[key] == DELETED)
    {
      table[key] = value;
      return key;
    }

    collisions++;

    i++;
  }

  return FAILED;
}

//search functions

int linearSearch(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = linearHash(value, i);

    if(table[key] == EMPTY)
    {
      return EMPTY;
    }
    else if(table[key] == value)
    {
      return key;
    }

    i++;
  }

  return EMPTY;
}

int quadraticSearch(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = quadraticHash(value, i);

    if(table[key] == EMPTY)
    {
      return EMPTY;
    }
    else if(table[key] == value)
    {
      return key;
    }

    i++;
  }

  return EMPTY;
}

int doubleSearch(int value)
{
  int i = 0;

  while(i < size)
  {
    int key = doubleHash(value, i);

    if(table[key] == EMPTY)
    {
      return EMPTY;
    }
    else if(table[key] == value)
    {
      return key;
    }

    i++;
  }

  return EMPTY;
}

//delete functions

void linearDelete(int key)
{
  table[key] = DELETED;
}

void quadraticDelete(int key)
{
  table[key] = DELETED;
}

void doubleDelete(int key)
{
  table[key] = DELETED;
}

//main

int main()
{
  table = new int[size];
  int collisionSum = 0;

  std::cout << "Linear" << std::endl;

  //linear
  for(int z = 0;z < 900;z++)
  {
    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = linearInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
  }

  for(int z = 0;z < 50;z++)
  {
    collisions = 0;

    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = linearInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
    else
    {
      std::cout << "inserted: " << randomInteger << " with " << collisions << " collisions" << std::endl;
    }

    collisionSum += collisions;
  }

  std::cout << "avg collisions: " << collisionSum/50 << std::endl;
  table = new int[size];
  std::cout << "Quadratic" << std::endl;

  //quadratic
  for(int z = 0;z < 900;z++)
  {
    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = quadraticInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
  }

  collisionSum = 0;

  for(int z = 0;z < 50;z++)
  {
    collisions = 0;

    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = quadraticInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
    else
    {
      std::cout << "inserted: " << randomInteger << " with " << collisions << " collisions" << std::endl;
    }

    collisionSum += collisions;
  }

  std::cout << "avg collisions: " << collisionSum/50 << std::endl;
  table = new int[size];
  std::cout << "Double" << std::endl;

  //double
  for(int z = 0;z < 900;z++)
  {
    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = doubleInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
  }

  collisionSum = 0;

  for(int z = 0;z < 50;z++)
  {
    collisions = 0;

    int randomInteger = rand() % RAND_MAX + 1;
    int resultKey = doubleInsert(randomInteger);

    //try again if insert fails
    if(resultKey == FAILED)
    {
      z--;
    }
    else
    {
      std::cout << "inserted: " << randomInteger << " with " << collisions << " collisions" << std::endl;
    }

    collisionSum += collisions;
  }

  std::cout << "avg collisions: " << collisionSum/50 << std::endl;

  return 0;
}
