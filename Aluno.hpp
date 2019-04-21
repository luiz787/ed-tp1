#ifndef TP1_ALUNO_HPP
#define TP1_ALUNO_HPP


#include <string>
#include <ostream>

class Aluno {
private:
    uint16_t id;
    std::string nome;
    double nota;
    uint16_t codigoPrimeiraOpcao;
    uint16_t codigoSegundaOpcao;

public:
    bool operator<(const Aluno &rhs) const;
    bool operator>(const Aluno &rhs) const;
    bool operator<=(const Aluno &rhs) const;
    bool operator>=(const Aluno &rhs) const;

    bool operator==(const Aluno &rhs) const;
    bool operator!=(const Aluno &rhs) const;

    Aluno();
    Aluno(uint16_t, std::string, double, uint16_t, uint16_t);

    uint16_t getId() const;
    const std::string &getNome() const;
    double getNota() const;
    uint16_t getCodigoPrimeiraOpcao() const;
    uint16_t getCodigoSegundaOpcao() const;

    friend std::ostream &operator<<(std::ostream &os, const Aluno &aluno);
};

#endif