#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>


#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50



//**Define donor structure **//
struct donor
{
    char name[50];
    int age;
    char phone_number[15];
    char address[100];
    char blood_group[5];
    char last_donation_date[15];
    bool active;
};



//** Function prototypes **//
void flash_screen();
void donor_registration();
void update_donor_details();
void deactivate_donor_account();
void delete_donor_account();
void list_all_donors();
void blood_request();
void blood_stock_report();
void search_blood();
void available_donors();





//** authentication **//
bool authenticate_user(char* username, char* password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




//** main function **//
int main()
{
    flash_screen();

    main_menu();

    return 0;
}





//** main menu function **//
void main_menu()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n");
    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("%*s%s%*s\n", 35, "", "|             Login Form               |", 35, "");
    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("\n");

    printf("\n");
    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("%*s%s%*s\n", 35, "", "|        Enter your username:          |", 35, "");
    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("\t\t\t\t\t\t     ");
    scanf("%s", username);

    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("%*s%s%*s\n", 35, "", "|        Enter your password:          |", 35, "");
    printf("%*s%s%*s\n", 35, "", "+--------------------------------------+", 35, "");
    printf("\t\t\t\t\t\t     ");
    scanf("%s", password);

    bool authenticated = authenticate_user(username, password);


    if (!authenticated)
    {
        printf("\n\033[31m          \t\t\t    .........AUTHENTICATION FAILED........\033[0m\n");
        exit(1);
    }
    else
    {
        printf("\033[1;32m\n          \t\t\t    ......SUCCESSFULLY AUTHENTICATED......\033[0m");
    }


    int choice;
    while (1)
    {
        printf("\n\n\n\n\033[1m\033[32m        ------------BLOOD DONATION SYSTEM MANAGEMENT MENU------------   \033[0m\n");
        printf("\033[2m        1. Search for blood\t\t\t");
        printf("  2. Register as donor \n");
        printf("        3. Update donor details\t\t\t");
        printf("  4. Deactivate donor account\n");
        printf("        5. Delete donor account\t\t\t");
        printf("  6. List all donors\n");
        printf("        7. Request blood\t\t\t");
        printf("  8. View blood stock report\n");
        printf("        9. View available donors\t\t");
        printf("  10.## Exit ##\n");
        printf("\033[0;95m\n        Enter your choice: \033[0m");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            search_blood();
            break;
        case 2:
            donor_registration();
            break;
        case 3:
            update_donor_details();
            break;
        case 4:
            deactivate_donor_account();
            break;
        case 5:
            delete_donor_account();
            break;
        case 6:
            list_all_donors();
            break;
        case 7:
            blood_request();
            break;
        case 8:
            blood_stock_report();
            break;
        case 9:
            available_donors();
            break;
        case 10:
            exit(0);
        default:
            printf("        \033[37mInvalid choice........Try again.\033[0m\n");
        }
    }
    return 0;
}






//** flash screen function **//
void flash_screen()
{
    system("cls");

    printf("\033[0;31m");

    printf("\n\n\n\n");
    printf("                                \033[0;34m### WELCOME ###\033[0;31m              \n");
    printf("\033[0;34m                   ******************************************\033[0;31m\n");
    printf("\n");
    printf("                   ******************************************\n");
    printf("                   **                                      **\n");
    printf("                   **          BLOOD DONATION              **\n");
    printf("                   **                                      **\n");
    printf("                   ******************************************\n");
    printf("                   **                                      **\n");
    printf("                   **         SYSTEM MANAGEMENT            **\n");
    printf("                   **                                      **\n");
    printf("                   ******************************************\n");
    printf("                   ******************************************\n");
    printf("\n");
    printf("\033[0;32m                          DONATE BLOOD   SAVE LIVES          \033[0;32m");
    printf("\n\n\n\n\n");
    printf("\033[1;36m                            PROJECT BY------\n\033[0m");
    printf("\033[1;36m                            S.M. Tahmid Abir.\n\033[0m");
    printf("\n\n");

    Sleep(3000);


    system("cls");
}








//** Donor registration function **//
void donor_registration()
{
    struct donor d;
    FILE *fp;
    fp = fopen("donors.dat", "a");

    if (fp == NULL)
    {
        printf("\033[1;31m        Error: could not open file for writing........\033[0m \n");
        return;
    }

    printf("\033[1;33m\n        Enter donor name: \033[0m");
    scanf("%s", d.name);
    printf("\033[1;33m        Enter donor age: \033[0m");
    scanf("%d", &d.age);
    printf("\033[1;33m        Enter phone number: \033[0m");
    scanf("%s", d.phone_number);
    printf("\033[1;33m        Enter address: \033[0m");
    scanf("%s", d.address);
    printf("\033[1;33m        Enter blood group (A+, B-, etc.): \033[0m");
    scanf("%s", d.blood_group);
    printf("\033[1;33m        Enter last donate date (dd/mm/yyyy): \033[0m");
    scanf("%s", d.last_donation_date);
    d.active = true;
    fwrite(&d, sizeof(struct donor), 1, fp);
    fclose(fp);
    printf("\n\033[0;32m        DONOR REGISTERED SUCCESSFULLY........\033[0;32m\n");

}








//** Update donor details function **//
void update_donor_details()
{
    int found = 0;
    char phone_number[15];
    struct donor d;

    FILE *fp, *temp;
    fp = fopen("donors.dat", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\033[1;31m        Error: could not open file.......\n\033[0m");
        return;
    }

    printf("\n\033[1;34m        Enter donor phone number to update details: \033[1;34m");
    scanf("%s", phone_number);

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.phone_number, phone_number) == 0)
        {
            found = 1;
            printf("\033[1;33m\n        Enter new donor name: \033[0m");
            scanf("%s", d.name);
            printf("\033[1;33m        Enter new donor age: \033[0m");
            scanf("%d", &d.age);
            printf("\033[1;33m        Enter new phone number: \033[0m");
            scanf("%s", d.phone_number);
            printf("\033[1;33m        Enter new address: \033[0m");
            scanf("%s", d.address);
            printf("\033[1;33m        Enter new blood group (A+, B-, etc.): \033[0m");
            scanf("%s", d.blood_group);
            printf("\033[1;33m        Enter new last donate date (dd/mm/yyyy): \033[0m");
            scanf("%s", d.last_donation_date);
            fwrite(&d, sizeof(struct donor), 1, temp);
            printf("\033[0;32m\n        DONOR DETAILS UPDATED SUCCESSFULLY........\n\033[0;32m");
        }

        else
        {
            fwrite(&d, sizeof(struct donor), 1, temp);
        }
    }

    if (!found)
    {
        printf("\n\033[1;31m        Error: donor not found with phone number: %s........\n\033[0m", phone_number);
    }

    fclose(fp);
    fclose(temp);
    remove("donors.dat");
    rename("temp.txt", "donors.dat");

}









//** Deactivate donor account function **//
void deactivate_donor_account()
{
    int found = 0;
    char phone_number[15];
    struct donor d;

    FILE *fp, *temp;
    fp = fopen("donors.dat", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\033[1;31m \n        Error: could not open file......\n\033[0m");
        return;
    }

    printf("\033[1;34m\n        Enter donor phone number to deactivate account: \033[1;34m");
    scanf("%s", phone_number);

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.phone_number, phone_number) == 0)
        {
            found = 1;
            d.active = 0;
            fwrite(&d, sizeof(struct donor), 1, temp);
            printf("\033[0;32m        DONOR ACCOUNT DEACTIVATED SUCCESSFULLY......\n\033[0;32m");
        }

        else
        {
            fwrite(&d, sizeof(struct donor), 1, temp);
        }
    }

    if (!found)
    {
        printf("\033[1;31m        Error: donor not found with phone number: %s.......\n\033[0m", phone_number);
    }

    fclose(fp);
    fclose(temp);
    remove("donors.dat");
    rename("temp.txt", "donors.dat");

}










//** Delete donor account function **//
void delete_donor_account()
{
    int found = 0;
    char phone_number[15];
    struct donor d;

    FILE *fp, *temp;
    fp = fopen("donors.dat", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\033[1;31m \n        Error: could not open file......\n\033[0m");
        return;
    }

    printf("\033[1;34m\n        Enter donor phone number to delete account: \033[1;34m");
    scanf("%s", phone_number);

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.phone_number, phone_number) == 0)
        {
            found = 1;
            printf("\033[1;34m        Are you sure you want to delete this donor account? ( Y / N ) : \033[1;34m");
            char confirm;
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                printf("\n\033[0;32m        DONOR ACCOUNT DELETED SUCCESSFULLY........\n\033[0;32m");
            }

            else
            {
                fwrite(&d, sizeof(struct donor), 1, temp);
            }

        }

        else
        {
            fwrite(&d, sizeof(struct donor), 1, temp);
        }
    }

    if (!found)
    {
        printf("\n\033[1;31m        Error: donor not found with phone number: %s.......\n\033[0m", phone_number);
    }

    fclose(fp);
    fclose(temp);
    remove("donors.dat");
    rename("temp.txt", "donors.dat");

}








//** all donor list function **//
void list_all_donors()
{
    struct donor d;
    FILE *fp;
    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        printf("\033[31m        Error: could not open file........\033[0m \n");
        return;
    }


    printf("\033[1;32m\n        LIST OF ALL DONORS INFORMATION----\n\033[0m");
    printf("\033[1;32m        +--------------+-----+--------------+----------------------+--------------+---------------------+\n");
    printf("        | Name         | Age | Phone Number | Address              | Blood Group  | Last Donation Date  |\n");
    printf("        +--------------+-----+--------------+----------------------+--------------+---------------------+\n\033[0m");


    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        printf("\033[1;32m        | %-12s | %3d | %-12s | %-20s | %-12s | %-19s |\n\033[0m",
               d.name, d.age, d.phone_number, d.address, d.blood_group, d.last_donation_date);
    }


    printf("\033[1;32m        +--------------+-----+--------------+----------------------+--------------+---------------------+\n\033[0m");

    fclose(fp);

}









//** Blood request function **//
void blood_request()
{
    char blood_group[5], location[100];
    struct donor d;
    int found = 0;
    FILE *fp;
    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        printf("\033[31m        Error: could not open file........\033[0m \n");
        return;
    }

    printf("\033[1;34m\n        Enter blood group required (e.g. A+, B-, AB+): \033[1;34m");
    scanf("%s", blood_group);
    printf("\033[1;34m        Enter location: \033[1;34m");
    scanf(" %[^\n]", location);
    printf("\n\033[0;32m        INFORMATION FOR THE REQUESTED BLOOD----\n\033[0;32m");
    printf("\033[1;32m        +-----------+-----+--------------+-----------------+-------------+---------------------+\n");
    printf("\033[1;32m        | Name      | Age | Phone Number | Address         | Blood Group | Last Donation Date  |\n");
    printf("\033[1;32m        +-----------+-----+--------------+-----------------+-------------+---------------------+\n");
    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.blood_group, blood_group) == 0 && strcmp(d.address, location) == 0)
        {
            found = 1;
            printf("\033[1;32m        | %-9s | %-3d | %-12s | %-15s | %-11s | %-19s |\n", d.name, d.age, d.phone_number, d.address, d.blood_group, d.last_donation_date);
        }
    }

    if (!found)
    {
        printf("\033[31m              %-72s    \n", "No donors found for this blood group......");
    }
    printf("\033[1;32m        +-----------+-----+--------------+-----------------+-------------+---------------------+\n");
    fclose(fp);

}











//** Blood stock report function **//
void blood_stock_report()
{
    char blood_group[5];
    int a_plus = 0, a_minus = 0, b_plus = 0, b_minus = 0, ab_plus = 0, ab_minus = 0, o_plus = 0, o_minus = 0;
    struct donor d;
    FILE *fp;

    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        printf("\033[31mError: could not open file.\033[0m\n");
        return;
    }

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.blood_group, "A+") == 0)
        {
            a_plus++;
        }
        else if (strcmp(d.blood_group, "A-") == 0)
        {
            a_minus++;
        }
        else if (strcmp(d.blood_group, "B+") == 0)
        {
            b_plus++;
        }
        else if (strcmp(d.blood_group, "B-") == 0)
        {
            b_minus++;
        }
        else if (strcmp(d.blood_group, "AB+") == 0)
        {
            ab_plus++;
        }
        else if (strcmp(d.blood_group, "AB-") == 0)
        {
            ab_minus++;
        }
        else if (strcmp(d.blood_group, "O+") == 0)
        {
            o_plus++;
        }
        else if (strcmp(d.blood_group, "O-") == 0)
        {
            o_minus++;
        }
    }

    fclose(fp);


    printf("\n\n\033[31m        BLOOD STOCK REPORT----\033[0m\n");
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | Group   | Number of Donors|\033[0m\n");
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | A+      | %15d |\033[0m\n", a_plus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | A-      | %15d |\033[0m\n", a_minus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | B+      | %15d |\033[0m\n", b_plus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | B-      | %15d |\033[0m\n", b_minus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | AB+     | %15d |\033[0m\n", ab_plus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | AB-     | %15d |\033[0m\n", ab_minus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | O+      | %15d |\033[0m\n", o_plus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");
    printf("\033[31m        | O-      | %15d |\033[0m\n", o_minus);
    printf("\033[31m        +---------+-----------------+\033[0m\n");

}












//**Search blood function **//
void search_blood()
{
    char blood_group[5];
    int found = 0;
    struct donor d;

    printf("\033[1;34m\n        Enter blood group to search: \033[1;34m");
    scanf("%s", blood_group);


    FILE *fp;
    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        printf("\033[31m        Error: could not open file.......\n        Please re-check your details\n\033[0m");
        search_blood();
        return;
    }

    printf("\033[1;33m\n        +------------------------------------+\n\033[0m");
    printf("\033[1;33m        | Donors with blood group %s:        |\n", blood_group);
    printf("\033[1;33m        +----------------+----+--------------+--------------+---------------------+\n\033[0m");
    printf("\033[1;33m        | Name           | Age| Phone Number | Address      | Last Donation Date  |\n\033[0m");
    printf("\033[1;33m        +----------------+----+--------------+--------------+---------------------+\n\033[0m");

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (strcmp(d.blood_group, blood_group) == 0)
        {
            printf("\033[1;33m        | %-14s | %2d | %-12s | %-12s | %-19s |\n", d.name, d.age, d.phone_number, d.address, d.last_donation_date);
            found = 1;
        }
    }

    printf("\033[1;33m        +----------------+----+--------------+--------------+---------------------+\n\033[0m");

    fclose(fp);

    if (!found)
    {
        printf("\033[31m        No donors found with blood group %s .......\n\033[0m", blood_group);
    }

}














//** Available donors function **//
void available_donors()
{
    int found = 0;
    struct donor d;

    printf("\033[1;36m\n        Available donors who have not donated blood in the last four months-----\n\033[0m");
    printf("\033[1;36m        +-----------------+-----+----------------+-----------------+-------------+--------------------+\n\033[0m");
    printf("\033[1;36m        | Name            | Age | Phone Number   | Address         | Blood Group | Last Donation Date |\n\033[0m");
    printf("\033[1;36m        +-----------------+-----+----------------+-----------------+-------------+--------------------+\n\033[0m");

    FILE *fp;
    fp = fopen("donors.dat", "rb");

    if (fp == NULL)
    {
        printf("\033[31m         | %-77s |\n", "Error: could not open file......\033[0m");
        printf("\033[1;36m        +-----------------+-----+----------------+-----------------+-------------+--------------------+\n\033[0m");
        return;
    }

    while (fread(&d, sizeof(struct donor), 1, fp))
    {
        if (is_available(d))
        {
            printf("\033[1;36m        | %-15s | %-3d | %-14s | %-15s | %-11s | %-18s |\n\033[0m", d.name, d.age, d.phone_number, d.address, d.blood_group, d.last_donation_date);
            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\033[31m       | %-77s |\n", "No available donors found........\033[0m");
        printf("\033[1;36m        +-----------------+-----+----------------+-----------------+-------------+--------------------+\n\033[0m");
    }

    else
    {
        printf("\033[1;36m        +-----------------+-----+----------------+-----------------+-------------+--------------------+\n\033[0m");
    }

}










//** Helper function for available donor function **//
int is_available(struct donor d)
{
    char *last_donation_date = d.last_donation_date;

    if (last_donation_date == NULL)
    {
        return 1;
    }

    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    int current_month = today->tm_mon + 1;
    int current_year = today->tm_year + 1900;
    int last_month, last_year;
    sscanf(last_donation_date, "%d/%d", &last_month, &last_year);

    if (current_year - last_year > 0 || current_month - last_month >= 4)
    {
        return 1;
    }

    return 0;

}




