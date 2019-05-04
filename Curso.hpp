#ifndef TP1_CURSO_HPP
#define TP1_CURSO_HPP

#include <string>
#include <ostream>
#include "Lista.hpp"
#include "Aluno.hpp"

class Curso {
private:
    uint16_t id;
    std::string nome;
    uint16_t quantidadeVagas;
    double notaCorte;
    Lista<Aluno> listaIntermediaria;
    Lista<Aluno> aprovados;
    Lista<Aluno> listaEspera;


    int compararAlunos(Aluno *a1, Aluno *a2) const;
    void marcarAlunoComoAprovado(Aluno *aluno) const;
    void marcarAlunoComoNaoAprovado(Aluno *alunoRemovido) const;
public:
    Curso();
    Curso(uint16_t, std::string, uint16_t);

    uint16_t getId() const;
    void adicionarAlunoListaIntermediaria(Aluno* aluno);
    void adicionarAlunoListaEspera(Aluno* aluno);
    void processarListaIntermediaria();
    void consolidarListaAprovados();

    bool operator<(const Curso &rhs) const;
    bool operator>(const Curso &rhs) const;
    bool operator<=(const Curso &rhs) const;
    bool operator>=(const Curso &rhs) const;

    bool operator==(const Curso &rhs) const;
    bool operator!=(const Curso &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Curso &curso);
};

#endif
