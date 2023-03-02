// Corvin Terzo and John Goceljak
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class Customer {
 public:
  int inTime;
  // int orderWaitRemaining;
  Customer *next;

  Customer(){
    inTime = -1;
    // orderWaitRemaining = -1;
    next = NULL;
  }
};

class Queue {
 public:
  Customer *head;

  Queue() { head = NULL; }

  void enqueue(int inTime) {
    Customer *temp = new Customer;
    temp->inTime = inTime;
    if (head == NULL) {
      head = temp;
    } else {
      temp->next = head;
      head = temp;
    }
  }

  bool queueEmpty(){
    if (head == NULL)
    {
      return true;
    }else{
      return false;
    }
  }

  int dequeue() {
    int startTime;
    if (head == NULL) {
      // cout << "Queue empty, nothing to remove\n";
      return -1;
    } else if (head->next == NULL) {
      startTime = head->inTime;
      delete head;
      head = NULL;
      return startTime;
    } else {
      Customer *chase, *follow;
      chase = follow = head;
      while (chase->next != NULL) {
        follow = chase;
        chase = chase->next;
      }
      follow->next = NULL;
      startTime = chase->inTime;
      delete chase;
      return startTime;
    }
  }

};

int main(){
  int TIME = 0;
  int generator;
  int queueHold = 0;
  int orderHold = 0;
  double averageWaitTimeSum = 0;
  double averageServiceTimeSum = 0;
  double averageQueueLengthSum = 0;
  int numOfCust = 0; // in order queue
  int bestWait = 0;
  int worstWait = 0;
  int bestService = 0;
  int worstService = 0;
  int startTime = 0;
  int totCust = 0;
  bool waitSet = false;
  bool serviceSet = false;
  bool queueSet = false;
  bool orderInProgress = false;
  int bestServiceTime = 0;
  int bestWaitTime = 0;
  int worstServiceTime = 0;
  int worstWaitTime = 0;
  int longestQueueTime = 0;
  int longestQueueLegnth = 0;
  Queue orderQueue;
  Queue pickUpQueue;
  srand(time(NULL));

// Store hours, every minute of a day
  while(TIME < 1020){
    // 1. should we add a new customore to the Q at this minute?
    if(TIME >= 0 && TIME < 120){
      // 8:00am through 10:00am
      generator = rand() % 100 + 1;
      if(generator <=30){
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if(TIME >= 120 && TIME < 210){
      // 10:00am through 11:30am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if (TIME >= 210 && TIME < 330) {
      // 11:30am through 1:30pm
      generator = rand() % 100 + 1;
      if (generator <= 40) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if (TIME >= 330 && TIME < 570) {
      // 1:30pm through 5:30pm
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if (TIME >= 570 && TIME < 720) {
      // 5:30pm through 8:00pm
      generator = rand() % 100 + 1;
      if (generator <= 25) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if (TIME >= 720 && TIME < 900) {
      // 8:00pm through 11:00pm
      generator = rand() % 100 + 1;
      if (generator <= 20) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }else if (TIME >= 900) {
      // 11:00pm through 1:00am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    }

    // 2. is a customer going to place an order this minute?
    if (!orderQueue.queueEmpty() && orderHold == 0 && !orderInProgress) {
      startTime = orderQueue.dequeue();
      int waitTime = TIME - startTime;
      averageWaitTimeSum += waitTime;
      numOfCust--;
      orderInProgress = true;
      orderHold = rand() % 6 + 1;
      if (!waitSet){
        bestWait = waitTime;
        worstWait = waitTime;
        waitSet = true;
      }else{
        if(bestWait > waitTime){
          bestWait = waitTime;
          bestWaitTime = startTime;
        }else if(worstWait < waitTime){
          worstWait = waitTime;
          worstWaitTime = startTime;
        }
      }
    }else if(!orderQueue.queueEmpty() && orderHold == 0 && orderInProgress){
      int serviceTime = TIME - startTime;
      // cout << "Order picked Up, start time " << startTime << "\n";
      averageServiceTimeSum += serviceTime;
      if (!serviceSet) {
        bestService = serviceTime;
        worstService = serviceTime;
        serviceSet = true;
      } else {
        if (bestService > serviceTime) {
          bestService = serviceTime;
          bestServiceTime = startTime;
        } else if (worstService < serviceTime) {
          worstService = serviceTime;
          worstServiceTime = startTime;
        }
      }
      orderInProgress = false;
    }else if (!orderQueue.queueEmpty() && orderHold > 0) {
      orderHold--;
    }

    // ***Code if one customer can order while the other waits for their food***
    // if (!orderQueue.queueEmpty()){
    //   int startTime = orderQueue.dequeue();
    //   int waitTime = TIME - startTime;
    //   averageWaitTimeSum += waitTime;
    //   numOfCust--;
    //   pickUpQueue.enqueue(startTime);
    //   orderHold = rand() % 6 + 1;
    //   if (!waitSet){
    //     bestWait = waitTime;
    //     worstWait = waitTime;
    //     waitSet = true;
    //   }else{
    //     if(bestWait > waitTime){
    //       bestWait = waitTime;
    //     }else if(worstWait < waitTime){
    //       worstWait = waitTime;
    //     }
    //   }
    // }

    // 3. is a customer ready to pick up an order this minute
    // if(orderHold > 0){
    //   orderHold--;
    // }else if(!pickUpQueue.queueEmpty()){
    //   int startTime = pickUpQueue.dequeue();
    //   int serviceTime = TIME - startTime;
    //   averageServiceTimeSum += serviceTime;
    //   if(!serviceSet){
    //     bestService = serviceTime;
    //     worstService = serviceTime;
    //     serviceSet = true;
    //   }else{
    //     if(bestService > serviceTime){
    //       bestService = serviceTime;
    //     }else if(worstService < serviceTime){
    //       worstService = serviceTime;
    //     }
    //   }
    // }

    // queue legnth calcs
    averageQueueLengthSum += numOfCust;
    TIME++;
    if (!queueSet){
      longestQueueTime = TIME;
      longestQueueLegnth = numOfCust;
      queueSet = true;
    }else{
      if(longestQueueLegnth < numOfCust){
        longestQueueLegnth = numOfCust;
        longestQueueTime = TIME;
      }
    }
  }

  // Calc and print averages
  averageWaitTimeSum /= totCust;
  averageServiceTimeSum /= totCust;
  averageQueueLengthSum /= 1020;

  cout << "Average Wait time: " << averageWaitTimeSum << "\n";
  cout << "Average Service Time: " << averageServiceTimeSum << "\n";
  cout << "Average Queue Length: " << averageQueueLengthSum << "\n";
  cout << "Fastest Wait Time: " << bestWait << "\n";
  cout << "Fastest Wait Time Occured At Time: " << bestWaitTime << "\n";
  cout << "Longest Wait Time: " << worstWait << "\n";
  cout << "Longest Wait Time Occured At Time: " << worstWaitTime << "\n";
  cout << "Fastest Service Time: " << bestService << "\n";
  cout << "Fastest Service Time Occured At Time: " << bestServiceTime << "\n";
  cout << "Longest Service Time: " << worstService << "\n";
  cout << "Longest Service Time Occured At Time: " << worstServiceTime << "\n";
  cout << "Shortest Queue: 0 @ Time 0"<< "\n";
  cout << "Longest Queue: " << longestQueueLegnth << "\n";
  cout << "Longest Queue Occured at Time: " << longestQueueTime << "\n";
}
