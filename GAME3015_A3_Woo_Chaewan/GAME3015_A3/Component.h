#pragma once

#include <memory>
#include "Command.h"

namespace GUI
{
    class CommandQueue;
    class Component
    {
    public:
        typedef std::shared_ptr<Component> Ptr;


    public:
        Component();
        virtual				~Component();

        virtual bool		isSelectable() const = 0;
        bool				isSelected() const;
        virtual void		select();
        virtual void		deselect();

        virtual bool		isActive() const;
        virtual void		activate();
        virtual void		deactivate();

        virtual void		handleEvent(CommandQueue& commands) = 0;


    private:
        bool				mIsSelected;
        bool				mIsActive;
    };

}