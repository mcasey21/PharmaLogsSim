// AUTHOR: Michael Casey 
// DATE: 03/04/2024
// DESCRIPTION: This project simulates and focuses on improving quality assurance processes within a pharmaceutical company's 
            //  manufacturing operations through IT solutions. There are four main tasks to be completed
            //  Task 1: Sort line logs by date & time and prepare reports sorted by product ID, issue code, date, 
            //          and time, with a target running time of O(NLog(N)) or better.
            //  Task 2: Generate reports using a single list to report issue codes by product ID and line ID 
            //          for all lines, aiming for a running time of O(N) or better.
            //  Task 3: Develop a search facility to find the earliest occurrence of an issue code for a given 
            //          product ID across all lines, with a running time of O(Log(N)) or better.
            //  Task 4: To produce a report summarizing the number of issues reported for a product 
            //          across all lines, with a running time of O(N) or better.



#include <stdio.h>

// Define a structure for date and time
typedef struct DateTime 
{
    int day;
    int hour;
    int minute;

} DateTime;

// Define a structure for resolution code and description
typedef struct ResolutionCode 
{
    int resolution_code;
    char resolution_description[100];

} ResolutionCode;

// Define a structure for line log entry
typedef struct LineLogEntry 
{
    int line_code;
    int batch_code;
    int product_id;
    int issue_code;
    DateTime date_time;
    ResolutionCode resolution;
    char issue_code_description[100];
    int reporting_employee_id;

} LineLogEntry;

// Merges them back together in a sorted manner
void merge1(LineLogEntry* arr, int, int, int right, LineLogEntry* temp);
// Divides the array into halves until it reaches subarrays of size 1
void mergeSort1(LineLogEntry* arr, int left, int right, LineLogEntry* temp);
// Merges all line logs together
void mergeLineLogs(LineLogEntry merged[], LineLogEntry arr1[], LineLogEntry arr2[], LineLogEntry arr3[], LineLogEntry arr4[], int size);
// Same as merge1 but with the merged line logs
void merge2(LineLogEntry arr[], int left, int mid, int right, LineLogEntry* temp);
// Same as mergesort1 but with merged line logs
void mergeSort2(LineLogEntry* arr, int left, int right, LineLogEntry* temp);


int main() 
{
    // order = line_code; batch_code; product_id; issue_code; date_time; resolution; issue_code_description; reporting_employee_id;
    LineLogEntry line_log1[] = 
    {
        {1, 2, 453, 107, {10, 8, 30}, {101, "Resolution description"}, "Issue description", 789},
        {1, 2, 892, 102, {10, 9, 15}, {102, "Resolution description"}, "Issue description", 987},
        {1, 1, 116, 103, {9, 11, 20}, {106, "Resolution description"}, "Issue description", 201},
        {1, 7, 453, 166, {11, 10, 0}, {103, "Resolution description"}, "Issue description", 654},
        {1, 4, 981, 123, {12, 18, 50}, {104, "Resolution description"}, "Issue description", 729},
        {1, 3, 321, 193, {9, 15, 30}, {105, "Resolution description"}, "Issue description", 223}
    };

    LineLogEntry line_log2[] = 
    {
        {2, 2, 116, 203, {8, 11, 15}, {101, "Resolution description"}, "Issue description", 789},
        {2, 3, 292, 123, {11, 18, 25}, {102, "Resolution description"}, "Issue description", 987},
        {2, 1, 453, 201, {11, 16, 20}, {106, "Resolution description"}, "Issue description", 201},
        {2, 8, 892, 205, {8, 8, 30}, {103, "Resolution description"}, "Issue description", 654},
        {2, 4, 321, 222, {10, 12, 40}, {104, "Resolution description"}, "Issue description", 729},
        {2, 1, 291, 123, {9, 15, 45}, {105, "Resolution description"}, "Issue description", 223}
    };

    LineLogEntry line_log3[] = 
    {
        {3, 6, 200, 301, {10, 10, 50}, {101, "Resolution description"}, "Issue description", 789},
        {3, 9, 981, 302, {11, 9, 55}, {102, "Resolution description"}, "Issue description", 987},
        {3, 1, 343, 332, {9, 16, 25}, {106, "Resolution description"}, "Issue description", 201},
        {3, 2, 321, 391, {9, 10, 20}, {103, "Resolution description"}, "Issue description", 654},
        {3, 4, 702, 221, {12, 13, 30}, {104, "Resolution description"}, "Issue description", 729},
        {3, 4, 702, 308, {9, 19, 10}, {105, "Resolution description"}, "Issue description", 223}
    };

    LineLogEntry line_log4[] = 
    {
        {4, 1, 321, 450, {9, 18, 10}, {101, "Resolution description"}, "Issue description", 789},
        {4, 2, 892, 401, {8, 9, 15}, {102, "Resolution description"}, "Issue description", 987},
        {4, 1, 200, 424, {9, 15, 50}, {106, "Resolution description"}, "Issue description", 201},
        {4, 3, 116, 499, {7, 14, 35}, {103, "Resolution description"}, "Issue description", 654},
        {4, 3, 116, 499, {10, 20, 40}, {104, "Resolution description"}, "Issue description", 729},
        {4, 6, 892, 410, {11, 11, 0}, {105, "Resolution description"}, "Issue description", 223}
    };

    // Gets size of each line log
    int num_entries1 = sizeof(line_log1) / sizeof(line_log1[0]);
    int num_entries2 = sizeof(line_log2) / sizeof(line_log2[0]);
    int num_entries3 = sizeof(line_log3) / sizeof(line_log3[0]);
    int num_entries4 = sizeof(line_log4) / sizeof(line_log4[0]);


    int i;

    printf("-------------------- TASK ONE --------------------\n");
    printf("Data from Line Log (sorted by date & time):\n\n");

    printf("------------ UNSORTED LOG LINE 1 ------------\n\n");
    for(i = 0; i < num_entries1; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log1[i].product_id, line_log1[i].issue_code,
               line_log1[i].date_time.day, line_log1[i].date_time.hour,
               line_log1[i].date_time.minute);
    }

    printf("------------ UNSORTED LOG LINE 2 ------------\n\n");
    for(i = 0; i < num_entries2; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log2[i].product_id, line_log2[i].issue_code,
               line_log2[i].date_time.day, line_log2[i].date_time.hour,
               line_log2[i].date_time.minute);
    }

    printf("------------ UNSORTED LOG LINE 3 ------------\n\n");
    for(i = 0; i < num_entries3; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log3[i].product_id, line_log3[i].issue_code,
               line_log3[i].date_time.day, line_log3[i].date_time.hour,
               line_log3[i].date_time.minute);
    }

    printf("------------ UNSORTED LOG LINE 4 ------------\n\n");
    for(i = 0; i < num_entries4; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log4[i].product_id, line_log4[i].issue_code,
               line_log4[i].date_time.day, line_log4[i].date_time.hour,
               line_log4[i].date_time.minute);
    }

    // Temp array for merge sort
    LineLogEntry temp1[num_entries1];
    LineLogEntry temp2[num_entries2];
    LineLogEntry temp3[num_entries3];
    LineLogEntry temp4[num_entries4];

    // Perform merge sort for date time
    mergeSort1(line_log1, 0, num_entries1 - 1, temp1);
    mergeSort1(line_log2, 0, num_entries2 - 1, temp2);
    mergeSort1(line_log3, 0, num_entries3 - 1, temp3);
    mergeSort1(line_log4, 0, num_entries4 - 1, temp4);

    printf("------------ SORTED LOG LINE 1 ------------\n\n");
    for(i = 0; i < num_entries1; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log1[i].product_id, line_log1[i].issue_code,
               line_log1[i].date_time.day, line_log1[i].date_time.hour,
               line_log1[i].date_time.minute);
    }

    printf("------------ SORTED LOG LINE 2 ------------\n\n");
    for(i = 0; i < num_entries2; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log2[i].product_id, line_log2[i].issue_code,
               line_log2[i].date_time.day, line_log2[i].date_time.hour,
               line_log2[i].date_time.minute);
    }

    printf("------------ SORTED LOG LINE 3 ------------\n\n");
    for(i = 0; i < num_entries3; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log3[i].product_id, line_log3[i].issue_code,
               line_log3[i].date_time.day, line_log3[i].date_time.hour,
               line_log3[i].date_time.minute);
    }

    printf("------------ SORTED LOG LINE 4 ------------\n\n");
    for(i = 0; i < num_entries4; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Date: %d, Time: %02d:%02d\n",
               line_log4[i].product_id, line_log4[i].issue_code,
               line_log4[i].date_time.day, line_log4[i].date_time.hour,
               line_log4[i].date_time.minute);
    }

    printf("\n\n-------------------- TASK TWO --------------------\n");
    printf("Issue Codes sorted by Product ID & Line Code\n\n");


    // Allocate sizes for the merged array
    int num_entries_merged = num_entries1 * 4;
    LineLogEntry line_log_merged[num_entries_merged];
    LineLogEntry temp_merged[num_entries_merged];


    mergeLineLogs(line_log_merged, line_log1, line_log2, line_log3, line_log4, num_entries1);
    mergeSort2(line_log_merged, 0, num_entries_merged - 1, temp_merged);

    for(i = 0; i<num_entries_merged; i++)
    {
        printf("Product ID: %d, Issue Code: %d, Line Code: %d\n",
                line_log_merged[i].product_id,
                line_log_merged[i].issue_code,
                line_log_merged[i].line_code);
    }


    printf("\n\n-------------------- TASK THREE --------------------\n");
    printf("Search for earliest occurence of an Issue Code\n\n");

    int user_issue_code;

    printf("Enter Issue Code: ");
    scanf("%d", &user_issue_code);

    int found = 0;

    // Searches through merged array for the issue code
    for(i = 0; i < num_entries_merged; i++)
    {
        if(line_log_merged[i].issue_code == user_issue_code) 
        {
            printf("Earliest occurrence of Issue Code %d",user_issue_code);
            printf("\n");
            printf("Product ID: %d, Issue Code: %d, Line Code: %d\n",
               line_log_merged[i].product_id, 
               line_log_merged[i].issue_code,
               line_log_merged[i].line_code);

            found = 1;
            break; // Breaks after first occurence to avoid printing duplicate values
        }
    }

    // If no issue code found print this
    if(!found)
    {
        printf("Issue Code %d not found in the log.\n", user_issue_code);
    }


    printf("\n\n-------------------- TASK FOUR --------------------\n");
    printf("Summarieses the number of issues reported for each product id\n");

    int last_seen = line_log_merged[0].product_id;
    int count = 0;

    // Searches through merged array for duplicate product_ids
    for(i = 0; i < num_entries_merged; i++)
    {

        if(last_seen == line_log_merged[i].product_id)
        {
            count++;
        }
        else
        {
            printf("\nProduct ID: %d, Issues Reported: %d", last_seen, count);

            // Update last_seen and reset count for the new product_id
            last_seen = line_log_merged[i].product_id;
            count = 1;
        }
        
    }

    // Print count for the last product_id
    printf("\nProduct ID: %d, Issues Reported: %d", last_seen, count);

    return 0;
}

void merge1(LineLogEntry* arr, int left, int mid, int right, LineLogEntry* temp) 
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while(i <= mid && j <= right) 
    {
        // Sort by product_id first
        if(arr[i].product_id < arr[j].product_id)
        {
            temp[k++] = arr[i++];
        }
        else if(arr[i].product_id > arr[j].product_id)
        {
            temp[k++] = arr[j++];
        }
        else // If product_ids are equal, sort by issue_code
        {
            if(arr[i].issue_code < arr[j].issue_code)
            {
                temp[k++] = arr[i++];
            }
            else if(arr[i].issue_code > arr[j].issue_code)
            {
                temp[k++] = arr[j++];
            }
            else // If product_ids and issue_codes are equal, sort by date_time
            {
                if(arr[i].date_time.day < arr[j].date_time.day ||
                    (arr[i].date_time.day == arr[j].date_time.day && arr[i].date_time.hour < arr[j].date_time.hour) ||
                    (arr[i].date_time.day == arr[j].date_time.day && arr[i].date_time.hour == arr[j].date_time.hour && arr[i].date_time.minute < arr[j].date_time.minute))
                {
                    temp[k++] = arr[i++];
                }
                else
                {
                    temp[k++] = arr[j++];
                }
            }
        }
    }

    while(i <= mid) 
    {
        temp[k++] = arr[i++];
    }

    while(j <= right) 
    {
        temp[k++] = arr[j++];
    }

    for(int l = left; l <= right; ++l) 
    {
        arr[l] = temp[l];
    }
}


void mergeSort1(LineLogEntry* arr, int left, int right, LineLogEntry* temp) 
{
    if(left < right) 
    {
        int mid = (left + right) / 2;
        mergeSort1(arr, left, mid, temp);
        mergeSort1(arr, mid + 1, right, temp);
        merge1(arr, left, mid, right, temp);
    }
}

void mergeLineLogs(LineLogEntry merged[], LineLogEntry arr1[], LineLogEntry arr2[], LineLogEntry arr3[], LineLogEntry arr4[], int size) 
{
    int mergedIndex = 0;

    // Merge arr1
    for (int i = 0; i < size; ++i) {
        merged[mergedIndex++] = arr1[i];
    }

    // Merge arr2
    for (int i = 0; i < size; ++i) {
        merged[mergedIndex++] = arr2[i];
    }

    // Merge arr3
    for (int i = 0; i < size; ++i) {
        merged[mergedIndex++] = arr3[i];
    }

    // Merge arr4
    for (int i = 0; i < size; ++i) {
        merged[mergedIndex++] = arr4[i];
    }
}

void merge2(LineLogEntry arr[], int left, int mid, int right, LineLogEntry* temp) 
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while(i <= mid && j <= right) 
    {
        if(arr[i].product_id < arr[j].product_id) 
            {
            temp[k++] = arr[i++];
        } 
        else 
        {
            temp[k++] = arr[j++];
        }
    }

    while(i <= mid) 
    {
        temp[k++] = arr[i++];
    }

    while(j <= right) 
    {
        temp[k++] = arr[j++];
    }

    for(int l = left; l <= right; ++l) 
    {
        arr[l] = temp[l];
    }
}

void mergeSort2(LineLogEntry* arr, int left, int right, LineLogEntry* temp) 
{
    if(left < right) 
    {
        int mid = (left + right) / 2;
        mergeSort2(arr, left, mid, temp);
        mergeSort2(arr, mid + 1, right, temp);
        merge2(arr, left, mid, right, temp);
    }
}