#ifndef REPOSITORY_EXCEPTIONS_H
#define REPOSITORY_EXCEPTIONS_H


#include <stdio.h>
#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
    std::string message;

public:
    FileException(const std::string& msg);
    virtual const char* what();
};

class RepositoryException : public std::exception
{
protected:
    std::string message;

public:
    RepositoryException();
    RepositoryException(const std::string& msg);
    virtual ~RepositoryException() {}
    virtual const char* what();
};

class DuplicateCoatException : public RepositoryException
{
    const char* what();
};

class DoesNotExist : public RepositoryException
{
    const char* what();
};

#endif // REPOSITORY_EXCEPTIONS_H
