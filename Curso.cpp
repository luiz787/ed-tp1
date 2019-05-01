#include "Curso.hpp"
#include <iomanip>
#include <iostream>

Curso::Curso() = default;

Curso::Curso(uint16_t id, std::string nome, uint16_t quantidadeVagas) : id(id), nome(std::move(nome)),
                                                              quantidadeVagas(quantidadeVagas),
                                                              quantidadeVagasRemanescentes(quantidadeVagas),
                                                              notaCorte(0),
                                                              aprovados(),
                                                              listaEspera() {}

uint16_t Curso::getId() const {
    return id;
}

void Curso::adicionarAlunoListaIntermediaria(Aluno* aluno) {
    if (this->listaIntermediaria.vazia()) {
        this->listaIntermediaria.adicionar(aluno);
    } else {
        this->listaIntermediaria.adicionarEmOrdemDescendente(aluno);
    }
}

void Curso::adicionarAlunoListaEspera(Aluno* aluno) {
    if (listaEspera.vazia()) {
        this->listaEspera.adicionar(aluno);
    } else {
        this->listaEspera.adicionarEmOrdemDescendente(aluno);
    }
}

void Curso::processarListaIntermediaria() {
    uint16_t quantidadeAprovados = 0;
    auto nodeAluno = this->listaIntermediaria.getPrimeiro();
    while (nodeAluno != nullptr) {
        if (quantidadeAprovados == this->quantidadeVagas) {
            /* variável auxiliar para manter a referência do próximo aluno, uma vez que nodeAluno será desalocado
             * em Lista::remover */
            auto prox = nodeAluno->getProximo();
            auto alunoRemovido = this->listaIntermediaria.remover(nodeAluno);
            marcarAlunoComoNaoAprovado(alunoRemovido);
            nodeAluno = prox;
        } else {
            auto aluno = nodeAluno->getValor();
            marcarAlunoComoAprovado(aluno);
            quantidadeAprovados++;
            nodeAluno = nodeAluno->getProximo();
        }
    }
}

void Curso::marcarAlunoComoAprovado(Aluno *aluno) const {
    if (id == aluno->getCodigoPrimeiraOpcao()) {
        aluno->setAprovadoPrimeiraOpcao(true);
    } else if (id == aluno->getCodigoSegundaOpcao()) {
        aluno->setAprovadoSegundaOpcao(true);
    }
}

void Curso::marcarAlunoComoNaoAprovado(Aluno *alunoRemovido) const {
    if (id == alunoRemovido->getCodigoPrimeiraOpcao()) {
        alunoRemovido->setAprovadoPrimeiraOpcao(false);
    } else if (id == alunoRemovido->getCodigoSegundaOpcao()) {
        alunoRemovido->setAprovadoSegundaOpcao(false);
    }
}

void Curso::consolidarListaAprovados() {
    auto nodeAluno = listaIntermediaria.getPrimeiro();
    uint16_t quantidadeAprovados = 0;
    while (nodeAluno != nullptr) {
        auto aluno = nodeAluno->getValor();
        aprovados.adicionar(aluno);
        quantidadeAprovados++;
        nodeAluno = nodeAluno->getProximo();
    }

    if (quantidadeAprovados == quantidadeVagas) {
        this->notaCorte = aprovados.getUltimo()->getValor()->getNota();
    }
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
