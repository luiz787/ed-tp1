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
    uint16_t quantidadeVagasRemanescentes;
    double notaCorte;
    Lista<Aluno> aprovados;
    Lista<Aluno> listaEspera;
public:
    bool operator<(const Curso &rhs) const;
    bool operator>(const Curso &rhs) const;
    bool operator<=(const Curso &rhs) const;
    bool operator>=(const Curso &rhs) const;

    bool operator==(const Curso &rhs) const;
    bool operator!=(const Curso &rhs) const;

    Curso();
    Curso(uint16_t, std::string, uint16_t);

    uint16_t getId() const;
    const std::string &getNome() const;
    uint16_t getQuantidadeVagas() const;
    uint16_t getQuantidadeVagasRemanescentes() const;
    double getNotaCorte() const;
    const Lista<Aluno> &getAprovados() const;
    const Lista<Aluno> &getListaEspera() const;
    void adicionarAlunoListaAprovados(Aluno* aluno);
    void adicionarAlunoListaEspera(Aluno* aluno);

    friend std::ostream &operator<<(std::ostream &os, const Curso &curso);
};

#endif
