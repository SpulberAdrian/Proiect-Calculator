#include <map>
#include <fstream>
#include <string>

class VariableManager {
private:
    std::map<std::string, double> variables;

public:
    void setVariable(const std::string& name, double value) {
        variables[name] = value;
    }

    double getVariable(const std::string& name) const {
        return variables.at(name);
    }

    void saveVariables(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        for (const auto& pair : variables) {
            file.write(pair.first.c_str(), pair.first.size());
            file.write(reinterpret_cast<const char*>(&pair.second), sizeof(double));
        }
    }

    void loadVariables(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        while (file) {
            std::string name;
            std::getline(file, name, '\0');
            double value;
            file.read(reinterpret_cast<char*>(&value), sizeof(double));
            variables[name] = value;
        }
    }
};