//--------------------------------------------
// Function: Enqueue()
// Purpose: Enqueue an item into the queue.
// Returns: TRUE if enqueue was successful
//        or FALSE if the enqueue failed.
//--------------------------------------------
int Enqueue(char ch)
{
    QNode *temp;

    // Check to see if the Queue is full
    if(isFull()) return FALSE;

    // Create new node for the queue
    temp = (QNode *)malloc(sizeof(QNode));
    temp->ch = ch;
    temp->next = NULL;

    // Check for inserting first in the queue
    if(head == NULL)
        head = tail = temp;
    else
    {
        tail->next = temp; // Insert into the queue
        tail = temp;       // Set tail to new last node
    }

    return TRUE;
}