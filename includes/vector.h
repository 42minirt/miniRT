#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

// vectoer
void    add_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void	neg_vec(t_vec *sub, t_vec *v1, t_vec *v2);
void	calc_outerproduct(t_vec *tgt_vec, t_vec *v1, t_vec *v2);
void    t_mix_vec_all(t_vec *tgt_vec, double t1, t_vec *v1, double t2, t_vec *v2);
void	setvec(t_vec *tgt_vec, double x, double y, double z);
void	normalize(t_vec *normal_vec, t_vec *normarized_vec);
void	inverse_vec(t_vec *inv_vec, t_vec *inved_vec);

#endif //VECTOR_H
