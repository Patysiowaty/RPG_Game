#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

class ICommand {
 public:
  virtual ~ICommand() = default;
  virtual void Execute() = 0;
};

#endif //ICOMMAND_HPP
