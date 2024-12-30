#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>

#include "TArray.h"

using namespace std;

class Book
{
public:
    Book() = default;
    
    Book(const string& InTitle, const string& InAuthor)
        : Title(InTitle), Author(InAuthor)
    {
        
    }

    string Title;
    string Author;
};


class BookManager
{

public:

    Book* AddBook(const string& InTitle, const string& InAuthor)
    {
        Books.PushBack(Book{InTitle, InAuthor});
        return &Books[Books.Num() - 1];
    }
    
    void DisplayAllBooks()
    {
        for(const auto& Book : Books)
        {
            cout << Book.Title << " " << Book.Author << "\n";
        }
    }
    
    Book* GetBookByTitle(const string& InTitle)
    {
            FindBookByTitle(InTitle);
    }
    
    Book* GetBookByAuthor(const string& InAuthor)
    {
        FindBookByAuthor(InAuthor);
    }

protected:
    Book* FindBookByTitle(const string& InTitle)
    {
        for(auto& Book : Books)
        {
            if(Book.Title == InTitle)
            {
                return &Book;
            }
        }
        return nullptr;
    }
    
    Book* FindBookByAuthor(const string& InAuthor)
    {
        for(auto& Book : Books)
        {
            if(Book.Author == InAuthor)
            {
                return &Book;
            }
        }
        return nullptr;
    }

private:
    TArray<Book> Books; 
};


class BorrowManager
{
 
public:
    void InitializeStock(Book* InBook, int Quantity = 3)
    {
        if(Stocks.find(InBook->Title) == Stocks.end())
        {
            Stocks[InBook->Title] = Quantity;    
        }
        else
        {
            cout << "Already Received..\n";
        }
    }
    void BorrowBook(const string& InTitle)
    {
        if(Stocks[InTitle])
        {
            --Stocks[InTitle];
        }
    }
    void ReturnBook(const string& InTitle)
    {
        ++Stocks[InTitle];
    }
    void DisplayStock()
    {
        for(const auto& [Title, Quantity] : Stocks)
        {
            cout << Title << " " << Quantity << "\n";
        }
    }

private:
    unordered_map<string, int> Stocks;
};