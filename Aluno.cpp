#include <utility>
#include <iomanip>

#include "Aluno.hpp"


Aluno::Aluno() = default;

Aluno::Aluno(uint16_t id, std::string nome,
             double nota, uint16_t codigoPrimeiraOpcao, uint16_t codigoSegundaOpcao) : id(id),
                                                                             nome(std::move(nome)),
                                                                             nota(nota),
                                                                             codigoPrimeiraOpcao(codigoPrimeiraOpcao),
                                                                             codigoSegundaOpcao(codigoSegundaOpcao) {}

uint16_t Aluno::getId() const {
    return id;
}

const std::string &Aluno::getNome() const {
    return nome;
}

double Aluno::getNota() const {
    return nota;
}

uint16_t Aluno::getCodigoPrimeiraOpcao() const {
    return codigoPrimeiraOpcao;
}

uint16_t Aluno::getCodigoSegundaOpcao() const {
    return codigoSegundaOpcao;
}

bool Aluno::operator==(const Aluno &rhs) const {
    return id == rhs.id &&
           nome == rhs.nome &&
           nota == rhs.nota &&
           codigoPrimeiraOpcao == rhs.codigoPrimeiraOpcao &&
           codigoSegundaOpcao == rhs.codigoSegundaOpcao;
}

bool Aluno::operator!=(const Aluno &rhs) const {
    return !(rhs == *this);
}

/**
 * Compara um aluno com o outro. Ordem de comparação: nota, nome (ordem alfabética), id (ordem de entrada).
 * @param rhs - outro aluno
 * @return true se esse aluno for "menor" que o outro, false caso contrário.
 */
bool Aluno::operator<(const Aluno &rhs) const {
    if (nota < rhs.nota) {
        return true;
    }
    if (rhs.nota < nota) {
        return false;
    }
    /*
     * Um aluno que foi inserido primeiro (com id menor) deve ser "maior".
     */
    if (id < rhs.id) {
        return false;
    }
    if (rhs.id < id) {
        return true;
    }

    return nome < rhs.nome;
}

bool Aluno::operator>(const Aluno &rhs) const {
    return rhs < *this;
}

bool Aluno::operator<=(const Aluno &rhs) const {
    return !(rhs < *this);
}

bool Aluno::operator>=(const Aluno &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Aluno &aluno) {
    os << std::fixed << std::setprecision(2) << aluno.nome << " " << aluno.nota;
    return os;
}
