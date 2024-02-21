#pragma once

#include "Command.h"
#include <queue>

/**
 * @brief A class representing a queue of commands.
 */
class CommandQueue
{
public:
    /**
     * @brief Push a command onto the queue.
     * @param command The command to push onto the queue.
     */
    void push(const Command& command);

    /**
     * @brief Pop a command from the queue.
     * @return The popped command.
     */
    Command pop();

    /**
     * @brief Check if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    bool isEmpty() const;

private:
    std::queue<Command> mQueue; /**< The underlying queue to store commands. */
};

