
#include "cg_local.h"

/*
===========================================
Weather Effects
GPL v3, by Rylius
Roughly inspired by Q3F Team
===========================================
*/

/*

#define MAX_WEATHER_PARTICLES 8192
#define RAIN_WEIGHT 1.1f
#define SNOW_WEIGHT 0.1f

#define WEATHER_RAIN 0
#define WEATHER_SNOW 1

#define ATMOSPHERIC_CUTHEIGHT 800

typedef struct cg_weatherParticle_s {
  vec3_t pos, delta, deltaNormalized, surfaceNormal;
  qhandle_t shader;
  qboolean active;
  float height;
  int surface, contents;
} cg_weatherParticle_t;

typedef struct cg_weatherEffect_s {
  cg_weatherParticle_t particles[MAX_WEATHER_PARTICLES];
  qhandle_t particleShader;
  qhandle_t waterShader, landShader;
  int particleNumber;
  float height;
} cg_weatherEffect_t;

static cg_weatherEffect_t weather;

static qboolean CG_RainParticleCheckVisible( cg_weatherParticle_t *particle ) {
  float moved;
  vec3_t distance;
  
  if (!particle || !particle->active) {
    return qfalse;
  }
  
  moved = (cg.time) * 0.001;
  VectorMA( particle->pos, moved, particle->delta, particle->pos);
  if( particle->pos[2] + ATMOSPHERIC_CUTHEIGHT) {
    return (particle->active = qfalse );
  }
  
  VectorSubtract( cg.refdef.vieworg, particle->pos, distance);
  if( sqrt( distance[0] * distance[0] + distance[1] * distance[1] ) > 800) {
    return( particle->active = qfalse );
  }

  return qtrue;
}

static qboolean CG_RainParticleGenerate(cg_weatherParticle_t *particle) {
  float angle, distance, origz;
  vec3_t testpoint, testend;
  trace_t tr;
  
  memset(&tr, 0, sizeof(tr));
  
  angle = random() * 2*M_PI;
  distance = 20 + 4096 * random();
  
  testpoint[0] = testend[0] = cg.refdef.vieworg[0] + sin(angle) * distance;
  testpoint[1] = testend[1] = cg.refdef.vieworg[1] + cos(angle) * distance;
  testpoint[2] = origz = cg.refdef.vieworg[2];
  testend[2] = testpoint[2] + 4096;
  
  while (qtrue) {
    if (testpoint[2] >= 4096 ) {
      return( qfalse );
    }
    if (testend[2] >= 4096) {
      testend[2] = 4096 - 1;
    }
    CG_Trace( &tr, testpoint, NULL, NULL, testend, ENTITYNUM_NONE, MASK_SOLID|MASK_WATER );
    if( tr.startsolid ) {
      testpoint[2] += 64;
      testend[2] = testpoint[2] + 4096;
    } else if ( tr.fraction == 1 ) {
      return( qfalse );
    } else if( tr.surfaceFlags & SURF_SKY ) {
      break;
    } else {
      return qfalse;
    }
  }

  particle->active = qtrue;
  VectorCopy( tr.endpos, particle->pos );
  VectorCopy( cg.refdef.vieworg, particle->delta );
  particle->delta[2] += crandom() * 100;
  VectorNormalize2( particle->delta, particle->deltaNormalized );
  particle->height = weather.height + crandom() * 100;
  particle->shader = weather.particleShader;

  distance = ((float)(tr.endpos[2] - -4096)) / -particle->delta[2];
  VectorMA(tr.endpos, distance, particle->delta, testend);

  CG_Trace(&tr, particle->pos, NULL, NULL, testend, ENTITYNUM_NONE, MASK_SOLID|MASK_WATER);
  tr.endpos[2]--;
  VectorCopy(tr.plane.normal, particle->surfaceNormal);
  particle->surface = tr.surfaceFlags;
  particle->contents = CG_PointContents(tr.endpos, ENTITYNUM_NONE);

  return qtrue;
}

void CG_EffectMark( qhandle_t markShader, const vec3_t origin, const vec3_t dir, float alpha, float radius ) {
  vec3_t axis[3];
  float texCoordScale;
  vec3_t originalPoints[4];
  byte colors[4];
  int i;
  polyVert_t *v;
  polyVert_t verts[4];

  if ( !cg_addMarks.integer ) {
    return;
  }

  if ( radius <= 0 ) {
    CG_Error( "CG_EffectMark called with <= 0 radius" );
  }

  // create the texture axis
  VectorNormalize2( dir, axis[0] );
  PerpendicularVector( axis[1], axis[0] );
  VectorSet( axis[2], 1, 0, 0 );  	  	  	// This is _wrong_, but the function is for water anyway (i.e. usually flat)
  CrossProduct( axis[0], axis[2], axis[1] );

  texCoordScale = 0.5 * 1.0 / radius;

  // create the full polygon
  for ( i = 0 ; i < 3 ; i++ ) {
    originalPoints[0][i] = origin[i] - radius * axis[1][i] - radius * axis[2][i];
    originalPoints[1][i] = origin[i] + radius * axis[1][i] - radius * axis[2][i];
    originalPoints[2][i] = origin[i] + radius * axis[1][i] + radius * axis[2][i];
    originalPoints[3][i] = origin[i] - radius * axis[1][i] + radius * axis[2][i];
  }

  colors[0] = 127;
  colors[1] = 127;
  colors[2] = 127;
  colors[3] = alpha * 255;

  for ( i = 0, v = verts ; i < 4 ; i++, v++ ) {
    vec3_t delta;
    VectorCopy( originalPoints[i], v->xyz );
    VectorSubtract( v->xyz, origin, delta );
    v->st[0] = 0.5 + DotProduct( delta, axis[1] ) * texCoordScale;
    v->st[1] = 0.5 + DotProduct( delta, axis[2] ) * texCoordScale;
    *(int *)v->modulate = *(int *)colors;
  }

  trap_R_AddPolyToScene(markShader, 4, verts);
}

static void CG_RainParticleRender( cg_weatherParticle_t *particle ) {
  vec3_t forward, right;
  polyVert_t verts[4];
  vec2_t line;
  float len, frac;
  vec3_t start, finish;

  if( !particle->active ) {
    return;
  }
  
  VectorCopy( particle->pos, start );
  len = particle->height;
  frac = start[2];
  VectorMA( start, len - particle->height, particle->deltaNormalized, start );
  frac = (ATMOSPHERIC_CUTHEIGHT + frac) / (float) ATMOSPHERIC_CUTHEIGHT;
  if (particle->contents & CONTENTS_WATER) {
    if( weather.waterShader && frac > 0 && frac < 1) {
      CG_EffectMark( weather.waterShader, start, particle->surfaceNormal, frac * 0.5, 8 - frac * 8 );
    }
  } else if( !( particle->surface & (SURF_NODAMAGE|SURF_NOIMPACT|SURF_NOMARKS|SURF_SKY) ) ) {
    if( weather.landShader && frac > 0 && frac < 1) {
      CG_EffectMark( weather.landShader, start, particle->surfaceNormal, frac * 0.5, 8 - frac * 8 );
    }
  }
  if (len <= 0) {
    return;
  }

  VectorCopy( particle->deltaNormalized, forward );
  VectorMA( start, -len, forward, finish );

  line[0] = DotProduct( forward, cg.refdef.viewaxis[1] );
  line[1] = DotProduct( forward, cg.refdef.viewaxis[2] );

  VectorScale( cg.refdef.viewaxis[1], line[1], right );
  VectorMA( right, -line[0], cg.refdef.viewaxis[2], right );
  VectorNormalize( right );

  VectorMA( finish, RAIN_WEIGHT, right, verts[0].xyz );
  verts[0].st[0] = 1;
  verts[0].st[1] = 0;
  verts[0].modulate[0] = 255;
  verts[0].modulate[1] = 255;
  verts[0].modulate[2] = 255;
  verts[0].modulate[3] = 0;

  VectorMA( finish, -RAIN_WEIGHT, right, verts[1].xyz );
  verts[1].st[0] = 0;
  verts[1].st[1] = 0;
  verts[1].modulate[0] = 255;
  verts[1].modulate[1] = 255;
  verts[1].modulate[2] = 255;
  verts[1].modulate[3] = 0;

  VectorMA( start, -RAIN_WEIGHT, right, verts[2].xyz );
  verts[2].st[0] = 0;
  verts[2].st[1] = 1;
  verts[2].modulate[0] = 255;
  verts[2].modulate[1] = 255;
  verts[2].modulate[2] = 255;
  verts[2].modulate[3] = 127;

  VectorMA( start, RAIN_WEIGHT, right, verts[3].xyz );
  verts[3].st[0] = 1;
  verts[3].st[1] = 1;
  verts[3].modulate[0] = 255;
  verts[3].modulate[1] = 255;
  verts[3].modulate[2] = 255;
  verts[3].modulate[3] = 127;

  trap_R_AddPolyToScene(particle->shader, 4, verts);
}

static void CG_AddWeather(void) {
  int curr, max, currnum;
  cg_weatherParticle_t *particle;

  if (weather.particleNumber <= 0) {
    return;
  }
  max = 8192;
  for (curr = 0; curr < max; curr++) {
    particle = &weather.particles[curr];
    CG_RainParticleRender(particle);
  }
}

static void CG_SetupWeather(void) {
  int count;
  
  weather.particleShader = trap_R_RegisterShader("gfx/weather/raindrop");
  weather.landShader = trap_R_RegisterShader("gfx/weather/landsplash");
  weather.waterShader = trap_R_RegisterShader("gfx/weather/watersplash");
  
  weather.particleNumber = 256;
  
  Com_Printf("^2CG_SetupWeather: Finished.\n");
}

 */