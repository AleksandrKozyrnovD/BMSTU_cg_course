#ifndef __BASE_COMMAND_H__
#define __BASE_COMMAND_H__


namespace Actions
{
    class BaseCommand
    {
    public:
        virtual ~BaseCommand() = default;
        virtual void Execute() = 0;
    };
}

#endif
