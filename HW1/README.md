# Basics
## Q1

**Maximum Profit**

Farzad's job is to receive several integers representing the profit or loss of the company on consecutive days. (The unit of numbers is in million Tomans.) He needs to determine the maximum profit the company has made. For example, on the first day, he was given these numbers: 
1, 2, -5, 4, -3, 2.

It is clear that the maximum profit the company made was on the fourth day, which equals 4 million Tomans. Since the sum of elements of any other subarray of this given array is smaller than 4. Note that if all the numbers were negative (indicating loss), the profit would be 0. Write a program so Farzad can perform his task without mental calculations.

**Input:**

The first line of input contains the number of days for which profit or loss is recorded, followed by an array of profits and losses on those days.

1 ≤ n ≤ 100

**Output:**

Your program should output the maximum profit.

**Example:**

Input:
12
7 -1 -2 1 5 -11 9 1 4 -1 3 -10



Output:
16

vbnet


Explanation: The maximum profit of the company is from day 7 to day 11, with the sum of numbers from day 7 to day 11 equal to 16.

Input:
5
-5 -2 -9 -1 -3


Output:
0

## Q2

**Eye to Eye**

In a metro car, we have two rows of seats facing each other, with each row consisting of 8 seats. Each seat is either empty or occupied by a person.

We know that if someone is sitting on seat number i, they only look directly across at themselves, meaning the seat number i in the opposite row. If someone is sitting on that seat, they make eye contact with each other.

You are given the seating arrangement of the passengers, and you need to determine the number of pairs making eye contact in a metro car.

**Input:**

The input consists of two lines, each containing 8 integers separated by a space, representing the seating arrangement of the metro car. 0 indicates an empty seat, and 1 indicates an occupied seat.

**Output:**

Output a single integer representing the number of pairs making eye contact.

**Example:**

Input:
1 1 0 1 0 0 1 1
1 1 0 0 0 1 0 1


Output:
3



Explanation: In this case, the pairs 1-2, 2-1, and 8-8 are making eye contact. Therefore, the answer is 3.

Input:
0 0 0 1 1 1 0 1
0 0 1 0 1 1 0 0


Output:
2

## Q3

**Matching Necklaces**

A father wants to buy two identical necklaces for his twin daughters so that the twins won't envy each other.

Determine whether the two necklaces are identical for different scenarios.

Note that rotating or flipping a necklace leaves it unchanged! Pay attention to the sample examples.

**Input:**

The first line contains an integer t, the number of pairs of necklaces to consider. Then, in each of the t following lines, a pair of necklaces separated by a space is given.

1≤t≤21844

Each necklace has a maximum length of 7 and consists of lowercase English letters.

**Output:**

For each pair indicating whether the two necklaces are identical, output YES or NO. Pay attention to the capitalization of your output.

**Example:**

Input:
6
ab abab
abc cba
gcd lcm
abc bca
lca lcs
abacb abcab



Output:
NO
YES
NO
YES
NO
YES

##  Q4
**Employee Hierarchy**

In engineering companies, there is a hierarchy among different employees. The first person in this hierarchy is the CEO, followed by lower-level managers and employees. Over time, new employees may be added to the company or leave the company. Additionally, the positions of two individuals in this hierarchy may be swapped. In this problem, you are required to apply changes to the hierarchy of company members and print the final hierarchy.



**Input**
First line: Number of company members
Next lines: Names of company members in the order of their position in the hierarchy
Next line: Number of hierarchy changes
Next lines: Changes, including swap, delete, or add operations.

**Output**
Final hierarchy of engineers. Explanation of changes:

After the first line, following an add operation, the name of the engineer added is given, and in the next line, their position number (starting from 0) is provided.

After the first line, following a delete operation, the name of the person to be removed from the hierarchy is given.

After two lines following a swap operation, the names of the engineers whose positions need to be swapped are given.

**Example**

Input

5
Alice
Bob
Carol
David
Emily
2
add
Frank
1
swap
Frank
David

Output

Alice David Bob Carol Frank Emily