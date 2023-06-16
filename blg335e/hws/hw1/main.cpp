#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

int BOOK_VECTOR_CAPACITY = 12000;

struct Book
{
    int bookID;
    std::string title;
    std::string authors;
    float average_rating;
    std::string isbn, isbn13;
    std::string language_code;
    int num_pages, ratings_count, text_reviews_count;
    std::string publication_date, publisher;
};

void removeCharacters(std::string &str, char character)
{
    std::string tmp_str;
    tmp_str.reserve(str.length());
    for (auto it = str.begin(); it != str.end(); it++)
    {
        if (*it == character)
        {
            continue;
        }
        tmp_str.push_back(*it);
    }
    str = tmp_str;
}

std::vector<Book> parseCSV(const std::string &file_path = "books.csv")
{
    std::vector<Book> books;
    books.reserve(BOOK_VECTOR_CAPACITY);
    auto file_stream = std::ifstream(file_path);
    std::string line;
    getline(file_stream, line); // To ignore the header line
    while (getline(file_stream, line))
    {
        std::istringstream line_stream(line);
        std::string attribute;
        std::string attribute_array[12];
        int array_index = 0;
        while (getline(line_stream, attribute, ','))
        { // To split each row by commas
            removeCharacters(attribute, '"');
            if (attribute == "")
            {
                attribute = "-1";
            }
            attribute_array[array_index] = attribute;
            array_index += 1;
        }
        books.push_back(Book{std::stoi(attribute_array[0]), attribute_array[1], attribute_array[2], std::stof(attribute_array[3]), attribute_array[4], attribute_array[5], attribute_array[6], std::stoi(attribute_array[7]), std::stoi(attribute_array[8]), std::stoi(attribute_array[9]), attribute_array[10], attribute_array[11]});
    }
    file_stream.close();
    return books;
}

void QS1(std::vector<Book> &arr, int start, int end, int &partition_count, int &swap_count)
{
    if (start >= end)
    {
        return;
    }

    int i = start;
    int j = start;
    float pivot = arr[end].average_rating;
    while (j <= end - 1 && arr[i].average_rating <= pivot && arr[j].average_rating <= pivot)
    {
        j++;
        i++;
    }
    while (arr[j].average_rating > pivot)
    {
        j++;
        Book tmp_i = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp_i;
        swap_count += 1;
        if (j == end)
        {
            break;
        }
        if (arr[i].average_rating <= pivot)
        {
            i++;
        }
    }

    partition_count += 1;
    
    QS1(arr, start, i - 1, partition_count, swap_count);
    QS1(arr, i + 1, end, partition_count, swap_count);
}

void runAndPrintStats(std::vector<Book> &arr, int arr_start, int arr_end)
{
    std::cout << "Before sorting:" << std::endl;
    for(int i = arr_start; i <= arr_end; i++) {
        std::cout << arr[i].bookID << "," << arr[i].average_rating << std::endl;
    }
    int partition_count = 0;
    int swap_count = 0;
    auto time_begin = std::chrono::steady_clock::now();
    QS1(arr, arr_start, arr_end, partition_count, swap_count);
    auto time_end = std::chrono::steady_clock::now();
    std::cout << "After sorting:" << std::endl;
    for(int i = arr_start; i <= arr_end; i++) {
        std::cout << arr[i].bookID << "," << arr[i].average_rating << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    std::cout << "Start index: " << arr_start << ", End index: " << arr_end << std::endl;
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count() << " ms" << std::endl;
    std::cout << "Partition count: " << partition_count << std::endl;
    std::cout << "Swap count: " << swap_count << std::endl;
    std::cout << "-----------------" << std::endl;
}

int main()
{
    std::vector<Book> original_books = parseCSV();
    std::vector<Book> books = original_books;
    runAndPrintStats(books, 0, books.size() / 4);
    books = original_books;
    runAndPrintStats(books, 0, books.size() / 2);
    books = original_books;
    runAndPrintStats(books, 0, books.size() - 1);
    std::ofstream output_file("sorted_books.csv");
    output_file << "bookID,average_rating" << std::endl;
    for (int i = 0; i < books.size(); i++)
    {
        output_file << books[i].bookID << "," << books[i].average_rating << std::endl;
    }
    output_file.close();
}