// Simple Bank Management System using Random Access File

#include <stdio.h>
#include <stdlib.h>

struct Bank
{
    int accNo;
    char name[20];
    float balance;
};

// Function Prototypes
void addAccount(FILE *fp);
void displayAccounts(FILE *fp);
void searchAccount(FILE *fp);
void depositAmount(FILE *fp);
void deleteAccount(FILE *fp);

int main()
{
    FILE *fp;
    int choice;

    fp = fopen("bank.dat", "rb+");

    // Create file if it does not exist
    if (fp == NULL)
    {
        fp = fopen("bank.dat", "wb+");

        if (fp == NULL)
        {
            printf("File cannot be created\n");
            exit(1);
        }
    }

    do
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Add Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Amount\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addAccount(fp);
            break;

        case 2:
            displayAccounts(fp);
            break;

        case 3:
            searchAccount(fp);
            break;

        case 4:
            depositAmount(fp);
            break;

        case 5:
            deleteAccount(fp);
            break;

        case 6:
            printf("Program Ended\n");
            break;

        default:
            printf("Invalid Choice\n");
        }

    } while (choice != 6);

    fclose(fp);

    return 0;
}

// Add new account
void addAccount(FILE *fp)
{
    struct Bank b;

    printf("Enter Account Number: ");
    scanf("%d", &b.accNo);

    printf("Enter Name: ");
    scanf("%s", b.name);

    printf("Enter Balance: ");
    scanf("%f", &b.balance);

    fseek(fp, 0, SEEK_END);
    fwrite(&b, sizeof(struct Bank), 1, fp);

    printf("Account Added Successfully\n");
}

// Display all accounts
void displayAccounts(FILE *fp)
{
    struct Bank b;

    rewind(fp);

    printf("\nAccNo\tName\tBalance\n");
    printf("--------------------------------\n");

    while (fread(&b, sizeof(struct Bank), 1, fp))
    {
        if (b.accNo != 0)
        {
            printf("%d\t%s\t%.2f\n", b.accNo, b.name, b.balance);
        }
    }
}

// Search account
void searchAccount(FILE *fp)
{
    struct Bank b;
    int acc, found = 0;

    printf("Enter Account Number to Search: ");
    scanf("%d", &acc);

    rewind(fp);

    while (fread(&b, sizeof(struct Bank), 1, fp))
    {
        if (b.accNo == acc)
        {
            printf("\nAccount Found\n");
            printf("Account No : %d\n", b.accNo);
            printf("Name       : %s\n", b.name);
            printf("Balance    : %.2f\n", b.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account Not Found\n");
    }
}

// Deposit amount
void depositAmount(FILE *fp)
{
    struct Bank b;
    int acc, found = 0;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    rewind(fp);

    while (fread(&b, sizeof(struct Bank), 1, fp))
    {
        if (b.accNo == acc)
        {
            printf("Current Balance: %.2f\n", b.balance);

            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            b.balance += amount;

            fseek(fp, -sizeof(struct Bank), SEEK_CUR);
            fwrite(&b, sizeof(struct Bank), 1, fp);

            printf("Amount Deposited Successfully\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account Not Found\n");
    }
}

// Delete account
void deleteAccount(FILE *fp)
{
    struct Bank b, empty = {0, "", 0};
    int acc, found = 0;

    printf("Enter Account Number to Delete: ");
    scanf("%d", &acc);

    rewind(fp);

    while (fread(&b, sizeof(struct Bank), 1, fp))
    {
        if (b.accNo == acc)
        {
            fseek(fp, -sizeof(struct Bank), SEEK_CUR);
            fwrite(&empty, sizeof(struct Bank), 1, fp);

            printf("Account Deleted Successfully\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account Not Found\n");
    }
}