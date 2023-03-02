// Corvin Terzo and John Goceljak
// two separate queues. The customer then picks the queue with lesser 
// customers in it and joins the line.

#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

class Customer {
 public:
  int inTime;
  // int orderWaitRemaining;
  Customer *next;

  Customer() {
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

  bool queueEmpty() {
    if (head == NULL) {
      return true;
    } else {
      return false;
    }
  }

  int getLength() {
    int count = 0;         
    Customer *current = head;  
    while (current != NULL) {
      count++;
      current = current->next;
    }
    return count;
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
  int orderHold = 0;
  int order2Hold = 0;
  double averageWaitTimeSum = 0;
  double averageServiceTimeSum = 0;
  double averageQueueLengthSum = 0;
  int numOfCust = 0; // in order queue
  int bestWait = 0;
  int worstWait = 0;
  int bestService = 0;
  int worstService = 0;
  int startTime = 0;
  int startTime2 = 0;
  int totCust = 0;
  bool waitSet = false;
  bool serviceSet = false;
  bool orderInProgress = false;
  bool order2InProgress = false;
  Queue orderQueue;
  Queue orderQueue2;
  srand(time(NULL));

// Store hours, every minute of a day
  while(TIME < 1020){
    // 1. should we add a new customore to the Q at this minute?
    if(TIME >= 0 && TIME < 120){
      // 8:00am through 10:00am (breakfast)
      generator = rand() % 100 + 1;
      if(generator <=30){
        if(orderQueue.getLength() > orderQueue2.getLength()){
          orderQueue2.enqueue(TIME);
        }else{
          orderQueue.enqueue(TIME);
        }
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
      // 11:30am through 1:30pm (lunch)
      generator = rand() % 100 + 1;
      if (generator <= 40) {
        if (orderQueue.getLength() > orderQueue2.getLength()) {
          orderQueue2.enqueue(TIME);
        } else {
          orderQueue.enqueue(TIME);
        }
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
      // 5:30pm through 8:00pm (dinner)
      generator = rand() % 100 + 1;
      if (generator <= 25) {
        if (orderQueue.getLength() > orderQueue2.getLength()) {
          orderQueue2.enqueue(TIME);
        } else {
          orderQueue.enqueue(TIME);
        }
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

    if (!orderQueue.queueEmpty() && orderHold == 0 && !orderInProgress) {
      startTime = orderQueue.dequeue();
      int waitTime = TIME - startTime;
      averageWaitTimeSum += waitTime;
      numOfCust--;
      orderInProgress = true;
      orderHold = rand() % 6 + 1;
      if (!waitSet) {
        bestWait = waitTime;
        worstWait = waitTime;
        waitSet = true;
      } else {
        if (bestWait > waitTime) {
          bestWait = waitTime;
        } else if (worstWait < waitTime) {
          worstWait = waitTime;
        }
      }
    } else if (!orderQueue.queueEmpty() && orderHold == 0 && orderInProgress) {
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
        } else if (worstService < serviceTime) {
          worstService = serviceTime;
        }
      }
      orderInProgress = false;
    } else if (!orderQueue.queueEmpty() && orderHold > 0) {
      orderHold--;
    }

    if (!orderQueue2.queueEmpty() && order2Hold == 0 && !order2InProgress) {
      startTime2 = orderQueue2.dequeue();
      int waitTime = TIME - startTime2;
      averageWaitTimeSum += waitTime;
      numOfCust--;
      order2InProgress = true;
      order2Hold = rand() % 6 + 1;
      if (!waitSet) {
        bestWait = waitTime;
        worstWait = waitTime;
        waitSet = true;
      } else {
        if (bestWait > waitTime) {
          bestWait = waitTime;
        } else if (worstWait < waitTime) {
          worstWait = waitTime;
        }
      }
    } else if (!orderQueue2.queueEmpty() && order2Hold == 0 && order2InProgress) {
      int serviceTime = TIME - startTime2;
      // cout << "Order picked Up, start time " << startTime << "\n";
      averageServiceTimeSum += serviceTime;
      if (!serviceSet) {
        bestService = serviceTime;
        worstService = serviceTime;
        serviceSet = true;
      } else {
        if (bestService > serviceTime) {
          bestService = serviceTime;
        } else if (worstService < serviceTime) {
          worstService = serviceTime;
        }
      }
      order2InProgress = false;
    } else if (!orderQueue2.queueEmpty() && order2Hold > 0) {
      order2Hold--;
    }

    averageQueueLengthSum += numOfCust;
    TIME++;
  }
  // Calc and print averages
  averageWaitTimeSum /= totCust;
  averageServiceTimeSum /= totCust;
  averageQueueLengthSum /= 1020;

  cout << "Average Wait time: " << averageWaitTimeSum << "\n";
  cout << "Average Service Time: " << averageServiceTimeSum << "\n";
  cout << "Average Queue Length: " << averageQueueLengthSum << "\n";
  cout << "Fastest Wait Time: " << bestWait << "\n";
  cout << "Longest Wait Time: " << worstWait << "\n";
  cout << "Fastest Service Time: " << bestService << "\n";
  cout << "Longest Service Time: " << worstService << "\n";
}