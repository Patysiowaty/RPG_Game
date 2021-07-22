#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

class ICommand {
 public:
  virtual void Execute() = 0;
  virtual ~ICommand() {}
};

#endif //ICOMMAND_HPP
