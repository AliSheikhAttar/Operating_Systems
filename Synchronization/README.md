# Synchronization

## Q1 - Calculating \( e \) Using Threads

In this question, you need to compute the value of \( e \) using threads. Write a program to calculate the series for \( e \) using the formula below, up to a specified number of terms.

\[ e = \sum_{k=0}^{\infty} \frac{1}{k!} \]

Make sure your program can work with different numbers of threads. For example, if you compute the series up to the 10 millionth term using 10 threads, each thread should calculate 1 million terms of the series.

## Q2 - Barber Sleeping

Implement a solution for the "Sleeping Barber" problem using synchronization techniques. In this problem, you need to simulate the operation of a barbershop with the following characteristics:

- **One barber** who cuts hair.
- **One barber chair** where the customer sits while the barber cuts their hair.
- **A waiting room** with a limited number of chairs for waiting customers.
- If there are no customers, the barber sits in the barber chair and sleeps.
- When a customer arrives:
  - If the barber is sleeping, the customer wakes up the barber and sits in the barber chair to get their hair cut.
  - If the barber is busy but there are empty chairs in the waiting room, the customer sits in one of the empty chairs and waits for their turn.
  - If the barber is busy and there are no empty chairs in the waiting room, the customer leaves the barbershop.

## Q3 - Restaurant Synchronization Chez

In this restaurant, there are \( N \) chefs hard at work in the kitchen. Each chef not only prepares delicious meals but also serves them to the customers while managing a limited storage space (Pantry). This scenario emphasizes the complexity of managing a limited pantry and the importance of resource sharing and synchronization to ensure smooth operation and prevent chaos.

In **Synchronization Chez**, there are \( N \) chefs, each with their own workstation. Between every pair of workstations, there is a shared cooking utensil (e.g., a knife). Each chef needs two utensils to prepare food: one on the left and one on the right.

When a dish is ready, the chef places it in their personal pantry, which has a limited capacity of \( C \) meals. If the pantry is full, the chef must wait until space is available. Additionally, each chef must serve the meals to the customers. If the pantry is empty, the chef must wait until food is prepared and available.

#### Kitchen Rules:
- **Food Preparation**: A chef can only prepare food if they have both the left and right utensils. This means that no two adjacent chefs can simultaneously use the same utensil.
- **Food Storage**: After preparing food, the chef stores it in their pantry. If the pantry is full, the chef must wait until there is free space.
- **Serving Food**: A chef can only serve food to customers if there is food in the pantry. If the pantry is empty, the chef must wait until a meal is available.
- **Returning to Work**: After serving food, the chef can continue preparing food if the utensils are available, thus continuing the cycle.


## Q4 - Suppliers and Agents Smokers (30 Points)

In a bustling city, there exists a peculiar neighborhood where three types of characters live: **Smokers**, **Agents**, and **Suppliers**. Smokers have an insatiable craving for cigarettes but lack some specific materials needed to make them. Agents have access to all the necessary materials but have no interest in smoking themselves. Each Supplier has only one specific material, but they are keen to trade with the Smokers.

The meeting point for these characters is at a strange corner of a street, where they need to coordinate their actions to fulfill their needs. However, there's a problem—they can only proceed when all three types of characters are present at the meeting point.

The challenge lies in synchronizing their actions at the meeting point to ensure that:

- **Smokers** can only smoke when they have all the necessary materials.
- **Agents** can only procure the constituent materials when both Smokers and Suppliers are present.
- **Suppliers** can only provide their constituent materials when both Smokers and Agents are present.

Given this scenario, design a synchronization mechanism to solve the meeting problem. To ensure proper coordination at the meeting point, implement the synchronization mechanism using a **barrier**. The barrier guarantees that no thread will proceed to the next phase until all threads have completed the current phase. Implement the synchronization mechanism with a barrier using only **mutexes**; the use of **semaphores** or **conditional variables** is not permitted.
