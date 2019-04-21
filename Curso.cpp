#include "Curso.hpp"
#include <iomanip>

Curso::Curso() = default;

Curso::Curso(uint16_t id, std::string nome, uint16_t quantidadeVagas) : id(id), nome(std::move(nome)),
                                                              quantidadeVagas(quantidadeVagas),
                                                              quantidadeVagasRemanescentes(quantidadeVagas),
                                                              notaCorte(0) {}

uint16_t Curso::getId() const {
    return id;
}

const std::string &Curso::getNome() const {
    return nome;
}

uint16_t Curso::getQuantidadeVagas() const {
    return quantidadeVagas;
}

uint16_t Curso::getQuantidadeVagasRemanescentes() const {
    return quantidadeVagasRemanescentes;
}

double Curso::getNotaCorte() const {
    return notaCorte;
}

const Lista<Aluno> &Curso::getAprovados() const {
    return aprovados;
}

const Lista<Aluno> &Curso::getListaEspera() const {
    return listaEspera;
}


bool Curso::operator==(const Curso &rhs) const {
    return id == rhs.id &&
           nome == rhs.nome &&
           quantidadeVagas == rhs.quantidadeVagas;
}

bool Curso::operator!=(const Curso &rhs) const {
    return !(rhs == *this);
}

bool Curso::operator<(const Curso &rhs) const {
    if (id < rhs.id) {
        return true;
    }
    if (rhs.id < id) {
        return false;
    }
    if (nome < rhs.nome) {
        return true;
    }
    if (rhs.nome < nome) {
        return false;
    }
    return quantidadeVagas < rhs.quantidadeVagas;
}

bool Curso::operator>(const Curso &rhs) const {
    return rhs < *this;
}

bool Curso::operator<=(const Curso &rhs) const {
    return !(rhs < *this);
}

bool Curso::operator>=(const Curso &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Curso &curso) {
    os << std::fixed << std::setprecision(2)
        << curso.nome << " " << curso.notaCorte << std::endl
        << "Classificados" << std::endl;
    Lista<Aluno> classificados = curso.aprovados;
    Node<Aluno>* aluno = classificados.getPrimeiro();
    while(aluno != nullptr) {
        os << *aluno->getValor() << std::endl;
        aluno = aluno->getProximo();
    }
    os << "Lista de espera" << std::endl;
    Lista<Aluno> listaEspera = curso.listaEspera;
    aluno = listaEspera.getPrimeiro();
    while (aluno != nullptr) {
        os << *aluno->getValor() << std::endl;
        aluno = aluno->getProximo();
    }
    return os;
}

void Curso::adicionarAlunoListaAprovados(Aluno* aluno) {
    this->aprovados.adicionar(aluno);
    this->quantidadeVagasRemanescentes--;
    if (quantidadeVagasRemanescentes == 0) {
        this->notaCorte = this->aprovados.getUltimo()->getValor()->getNota();
    }
}

void Curso::adicionarAlunoListaEspera(Aluno* aluno) {
    this->listaEspera.adicionar(aluno);
}
