#include <utility>
#include <iomanip>

#include "Aluno.hpp"


Aluno::Aluno() = default;

Aluno::Aluno(uint16_t id, std::string nome,
             double nota, uint16_t codigoPrimeiraOpcao, uint16_t codigoSegundaOpcao) : id(id),
                                                                             nome(std::move(nome)),
                                                                             nota(nota),
                                                                             codigoPrimeiraOpcao(codigoPrimeiraOpcao),
                                                                             codigoSegundaOpcao(codigoSegundaOpcao),
                                                                             aprovadoPrimeiraOpcao(false),
                                                                             aprovadoSegundaOpcao(false),
                                                                             rejeitado(false) {}

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

bool Aluno::isAprovadoPrimeiraOpcao() const {
    return aprovadoPrimeiraOpcao;
}

void Aluno::setAprovadoPrimeiraOpcao(bool aprovado) {
    this->aprovadoPrimeiraOpcao = aprovado;
}

bool Aluno::isAprovadoSegundaOpcao() const {
    return aprovadoSegundaOpcao;
}

void Aluno::setAprovadoSegundaOpcao(bool aprovado) {
    this->aprovadoSegundaOpcao = aprovado;
}

bool Aluno::isRejeitado() const {
    return rejeitado;
}

void Aluno::setRejeitado(bool rejeitado) {
    this->rejeitado = rejeitado;
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
 * Compara um aluno com o outro. Ordem de comparação: nota, id (ordem de entrada).
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

    return id > rhs.id; // Um aluno que foi inserido depois que outro (com id maior) deve ser "menor".
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
