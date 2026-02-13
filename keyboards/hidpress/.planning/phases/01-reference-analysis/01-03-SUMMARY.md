---
phase: 01-reference-analysis
plan: 03
subsystem: documentation
tags: [qmk, vial, split-keyboard, fix-checklist, requirements-traceability, eeprom, matrix-config]

# Dependency graph
requires:
  - phase: 01-02
    provides: "REFERENCE-ANALYSIS.md with comparison tables, EEPROM calculations, position maps"
provides:
  - "FIX-CHECKLIST.md with phase-organized actionable checklist covering all 15 requirements"
  - "Complete right-half position remap table (25 keys, rows 0-3 to 4-7) ready for Phase 3"
  - "Quick reference values table for downstream copy-paste"
  - "Requirement coverage matrix confirming 100% requirement coverage"
  - "Scope validation confirming no scope creep in any checklist item"
affects: [02-matrix-dimension-audit, 03-vial-json-fix, 04-peripheral-matrix-mapping, 05-eeprom-budget, 06-defensive-eeprom, 07-build-flash, 08-verification]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Phase-organized fix checklist with requirement IDs, file paths, current/target values, and reference citations"
    - "Three-state checkbox convention: [ ] todo, [x] completed, [~] already correct"
    - "Physical user actions annotated separately from Claude-automatable tasks"

key-files:
  created:
    - ".planning/phases/01-reference-analysis/FIX-CHECKLIST.md"
  modified: []

key-decisions:
  - "Checklist items include specific file paths, current values, and target values so Phase 2-8 executors never re-read source files"
  - "Phase 7-8 items annotated as physical user actions since Claude cannot flash or test hardware"
  - "Requirement coverage matrix added as explicit validation section at end of document"

patterns-established:
  - "Fix checklist format: each item has requirement ID, file path, current/target values, and REFERENCE-ANALYSIS.md section citation"
  - "Scope validation section at end of deliverable documents to confirm no scope creep"

# Metrics
duration: 3min
completed: 2026-02-13
---

# Phase 1 Plan 3: Fix Checklist Summary

**Phase-organized fix checklist with all 15 requirements mapped across 8 phases, 25-key position remap table, quick reference values, and explicit scope validation**

## Performance

- **Duration:** 3 min
- **Started:** 2026-02-13T12:29:44Z
- **Completed:** 2026-02-13T12:32:48Z
- **Tasks:** 2
- **Files created:** 1

## Accomplishments
- Created FIX-CHECKLIST.md as the primary Phase 1 deliverable, providing actionable checklist items for all 8 phases
- Every checklist item includes requirement ID, specific file path, current/target values, and REFERENCE-ANALYSIS.md section citation
- All 15 project requirements (MTRX-01 through MTRX-06, EEPR-01 through EEPR-04, DFNS-01 through DFNS-02, XVAL-01 through XVAL-03) verified present
- Complete 25-key right-half position remap table carried forward from REFERENCE-ANALYSIS.md into executable Phase 3 checklist format
- Quick reference values table provides all key numbers (MATRIX_ROWS=8, layer_size=128, total EEPROM=512, etc.) for downstream copy-paste
- Scope validation section confirms no items add new features, modify out-of-scope files, or touch working subsystems

## Task Commits

Each task was committed atomically:

1. **Task 1: Derive core fix categories and Phase 1-4 checklist sections** - `533acd706c` (feat)
2. **Task 2: Add Phase 5-8 sections, constraints, quick reference, and validate requirement coverage** - `41e3d6f98e` (feat)

**Plan metadata:** (pending)

## Files Created/Modified
- `.planning/phases/01-reference-analysis/FIX-CHECKLIST.md` - Phase-organized fix checklist with all 15 requirements, position maps, constraints, and quick reference values

## Decisions Made
- Included specific file paths and current/target values in every checklist item so downstream executors are self-sufficient
- Annotated Phase 7-8 items as "physical user action" since Claude cannot flash firmware or test hardware
- Added requirement coverage matrix and scope validation as explicit sections for auditability

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered
None.

## User Setup Required
None - no external service configuration required.

## Next Phase Readiness
- Phase 1 is now complete (all 3 plans executed)
- FIX-CHECKLIST.md is ready for use by Phase 2 (Matrix Dimension Audit) as the source of truth for what needs checking
- Phase 3 can use the checklist's 25-key position remap table directly for the vial.json fix
- Phase 5 can use the quick reference values for EEPROM budget calculations
- All Phase 1 success criteria from ROADMAP.md are satisfied:
  1. Sofle rev1 Vial config documented and confirmed matching (REFERENCE-ANALYSIS.md)
  2. Sofle right-half row numbers documented (REFERENCE-ANALYSIS.md Section 8)
  3. Sofle encoder mapping documented (REFERENCE-ANALYSIS.md Section 7)
  4. Clear "what Sofle does that Ambi must also do" checklist exists (FIX-CHECKLIST.md)

## Self-Check: PASSED

- FIX-CHECKLIST.md: FOUND
- 01-03-SUMMARY.md: FOUND
- Commit 533acd706c: FOUND
- Commit 41e3d6f98e: FOUND

---
*Phase: 01-reference-analysis*
*Completed: 2026-02-13*
